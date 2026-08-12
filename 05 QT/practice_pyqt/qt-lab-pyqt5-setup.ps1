# ==============================================================
#  PyQt5 environment setup for Windows   (qt-lab5)
#  - creates %USERPROFILE%\qt-lab5
#  - creates a .venv inside it
#  - installs PyQt5 (+ PyQt5-tools, for Qt Designer)
#  - writes a small sample project (main.py, run.bat, designer.bat)
#  Console messages are ASCII on purpose (console codepage safety).
# ==============================================================

$ErrorActionPreference = 'Continue'
$ProgressPreference    = 'SilentlyContinue'

$Here       = Split-Path -Parent $MyInvocation.MyCommand.Definition
$ProjectDir = Join-Path $env:USERPROFILE 'qt-lab5'
$VenvDir    = Join-Path $ProjectDir '.venv'
$VenvPy     = Join-Path $VenvDir 'Scripts\python.exe'
$LogFile    = Join-Path $Here 'qt-lab5-setup-log.txt'

if (Test-Path -LiteralPath $LogFile) { Remove-Item -LiteralPath $LogFile -Force }

function Log([string]$msg) {
    $line = "[{0}] {1}" -f (Get-Date -Format 'HH:mm:ss'), $msg
    Write-Host $line
    Add-Content -LiteralPath $LogFile -Value $line
}

function Run([string]$title, [scriptblock]$block) {
    Log ("--> " + $title)
    $global:LASTEXITCODE = 0
    $out = & $block 2>&1
    $code = $global:LASTEXITCODE
    if ($null -eq $code) { $code = 0 }
    foreach ($l in $out) { Add-Content -LiteralPath $LogFile -Value ("    " + $l) }
    return $code
}

function Fail([string]$step, [string]$detail) {
    Log ("ERROR at [{0}]: {1}" -f $step, $detail)
    Log "RESULT: FAIL"
    Write-Host ""
    Write-Host "Setup did NOT finish."
    Write-Host "Log file: $LogFile"
    Read-Host "Press Enter to close"
    exit 1
}

Log "=== qt-lab5 / PyQt5 setup started ==="
Log ("script folder  : " + $Here)
Log ("project folder : " + $ProjectDir)
Log ("windows        : " + [System.Environment]::OSVersion.VersionString)
Log ("powershell     : " + $PSVersionTable.PSVersion.ToString())

# --------------------------------------------------------------
# 1. locate a usable Python
# --------------------------------------------------------------
function Get-PyVersion($exe, $extraArgs) {
    try {
        $global:LASTEXITCODE = 0
        $v = & $exe @extraArgs -c "import sys;print('%d.%d.%d'%sys.version_info[:3])" 2>$null
        if ($global:LASTEXITCODE -eq 0 -and $v) { return ("" + $v).Trim() }
    } catch { }
    return $null
}

$cands = @(
    @{ exe = 'py';      args = @('-3') },
    @{ exe = 'python';  args = @()     },
    @{ exe = 'python3'; args = @()     }
)

$PyExe = $null; $PyArgs = @(); $PyVer = $null
foreach ($c in $cands) {
    $v = Get-PyVersion $c.exe $c.args
    if ($v) { $PyExe = $c.exe; $PyArgs = $c.args; $PyVer = $v; break }
}

if (-not $PyExe) {
    Log "No Python found on PATH. Trying: winget install Python.Python.3.12 (user scope)"
    if (Get-Command winget -ErrorAction SilentlyContinue) {
        Run "winget install python" { winget install --id Python.Python.3.12 -e --scope user --silent --accept-package-agreements --accept-source-agreements } | Out-Null
        $env:Path = [System.Environment]::GetEnvironmentVariable('Path','Machine') + ';' + [System.Environment]::GetEnvironmentVariable('Path','User')
        foreach ($c in $cands) {
            $v = Get-PyVersion $c.exe $c.args
            if ($v) { $PyExe = $c.exe; $PyArgs = $c.args; $PyVer = $v; break }
        }
    } else {
        Log "winget is not available on this machine."
    }
}

if (-not $PyExe) {
    Fail 'python-detect' 'Python 3.8+ not found. Install it from https://www.python.org/downloads/ (tick "Add python.exe to PATH") and run this again.'
}

$parts = $PyVer.Split('.')
if (([int]$parts[0] -lt 3) -or ([int]$parts[0] -eq 3 -and [int]$parts[1] -lt 8)) {
    Fail 'python-version' ("Found Python $PyVer but PyQt5 needs 3.8 or newer.")
}

$PyPath = & $PyExe @PyArgs -c "import sys;print(sys.executable)"
Log ("python         : {0} {1}   v{2}" -f $PyExe, ($PyArgs -join ' '), $PyVer)
Log ("python path    : " + $PyPath)

# --------------------------------------------------------------
# 2. project folder + sample project files
# --------------------------------------------------------------
if (-not (Test-Path -LiteralPath $ProjectDir)) {
    New-Item -ItemType Directory -Force -Path $ProjectDir | Out-Null
    Log "created project folder"
} else {
    Log "project folder already exists, reusing it"
}

$MainPy = @'
import sys
from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QVBoxLayout


def main():
    app = QApplication(sys.argv)

    window = QWidget()
    window.setWindowTitle("qt-lab5 (PyQt5)")
    window.resize(360, 160)

    layout = QVBoxLayout()
    label = QLabel("PyQt5 is working!")
    layout.addWidget(label)
    window.setLayout(layout)

    window.show()
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()
'@

$CheckEnvPy = @'
import sys

try:
    from PyQt5 import QtCore
except ImportError as exc:
    print("PyQt5 import failed:", exc)
    sys.exit(1)

print("Python  :", sys.version.split()[0])
print("PyQt5   :", QtCore.PYQT_VERSION_STR)
print("Qt      :", QtCore.QT_VERSION_STR)
print("OK")
'@

$RunBat = @'
@echo off
call "%~dp0.venv\Scripts\activate.bat"
python "%~dp0main.py"
'@

$DesignerBat = @'
@echo off
set DESIGNER="%~dp0.venv\Scripts\pyqt5-tools.exe"
if exist %DESIGNER% (
    %DESIGNER% designer
) else (
    echo pyqt5-tools designer not found. Re-run the setup script.
    pause
)
'@

Set-Content -LiteralPath (Join-Path $ProjectDir 'main.py')       -Value $MainPy       -Encoding UTF8
Set-Content -LiteralPath (Join-Path $ProjectDir 'check_env.py')  -Value $CheckEnvPy   -Encoding UTF8
Set-Content -LiteralPath (Join-Path $ProjectDir 'run.bat')       -Value $RunBat       -Encoding ASCII
Set-Content -LiteralPath (Join-Path $ProjectDir 'designer.bat')  -Value $DesignerBat  -Encoding ASCII
Log "wrote sample project files (main.py, check_env.py, run.bat, designer.bat)"

# --------------------------------------------------------------
# 3. virtual environment
# --------------------------------------------------------------
if (-not (Test-Path -LiteralPath $VenvPy)) {
    $code = Run "creating virtual environment (.venv)" { & $PyExe @PyArgs -m venv "$VenvDir" }
    if (-not (Test-Path -LiteralPath $VenvPy)) {
        Fail 'venv' ("could not create .venv (exit code $code). If Python came from the Microsoft Store, install it from python.org instead.")
    }
} else {
    Log "reusing existing .venv"
}
Log ("venv python    : " + $VenvPy)

# --------------------------------------------------------------
# 4. packages
# --------------------------------------------------------------
$code = Run "upgrading pip / setuptools / wheel" { & $VenvPy -m pip install --upgrade pip setuptools wheel }
if ($code -ne 0) { Log "WARN: pip upgrade returned $code (continuing)" }

$code = Run "installing PyQt5" { & $VenvPy -m pip install "PyQt5>=5.15,<6" }
if ($code -ne 0) { Fail 'pyqt5' "pip install PyQt5 failed with exit code $code - see the lines above in this log." }

$designerOk = $true
$code = Run "installing pyqt5-tools  (Qt Designer app)" { & $VenvPy -m pip install pyqt5-tools }
if ($code -ne 0) {
    $designerOk = $false
    Log "WARN: pyqt5-tools failed. PyQt5 itself is fine; only Qt Designer is unavailable."
}

# --------------------------------------------------------------
# 5. verification
# --------------------------------------------------------------
$code = Run "verifying the environment" { & $VenvPy (Join-Path $ProjectDir 'check_env.py') }
if ($code -ne 0) { Fail 'verify' "check_env.py failed with exit code $code - see the lines above in this log." }

Run "writing requirements-lock.txt" {
    & $VenvPy -m pip freeze | Out-File -FilePath (Join-Path $ProjectDir 'requirements-lock.txt') -Encoding ascii
} | Out-Null

$designerExe = Join-Path $VenvDir 'Scripts\pyqt5-tools.exe'
if (Test-Path -LiteralPath $designerExe) {
    Log ("qt designer    : " + $designerExe)
} else {
    $designerOk = $false
    Log "qt designer    : NOT INSTALLED"
}

# --------------------------------------------------------------
# 6. done
# --------------------------------------------------------------
Copy-Item -LiteralPath $LogFile -Destination (Join-Path $ProjectDir 'setup-log.txt') -Force -ErrorAction SilentlyContinue

if ($designerOk) { Log "RESULT: OK" } else { Log "RESULT: OK_NO_DESIGNER" }

Write-Host ""
Write-Host "============================================================"
Write-Host " Done.   $ProjectDir"
Write-Host ""
Write-Host "   run.bat        - launch the sample PyQt5 app"
Write-Host "   designer.bat   - open Qt Designer"
Write-Host "   check_env.py   - verify the environment manually"
Write-Host "============================================================"
Write-Host ""
Read-Host "Press Enter to close"