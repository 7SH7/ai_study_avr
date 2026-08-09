import sys, os, subprocess
from PyQt5.QtWidgets import *

MAIN_FILE_NAME = 'main_wnd'
DIALOG_FILE_NAME = 'dialog'
subprocess.run([
    sys.executable,          
    '-m', 'PyQt5.uic.pyuic', 
    '-x', f'{MAIN_FILE_NAME}.ui', 
    '-o', f'{MAIN_FILE_NAME}.py'
])
subprocess.run([
    sys.executable,          
    '-m', 'PyQt5.uic.pyuic', 
    '-x', f'{DIALOG_FILE_NAME}.ui', 
    '-o', f'{DIALOG_FILE_NAME}.py'
])
from main_wnd import Ui_MainWindow
from dialog import Ui_Dialog
from PyQt5.QtCore import Qt


class Form(QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.btnExec.clicked.connect(self.exec_dialog)
        self.btnOpen.clicked.connect(self.open_dialog)
        self.btnShow.clicked.connect(self.show_dialog)

    def exec_dialog(self):
        print('******** exec clicked *******')
        dlg = dlgForm(self)
        dlg.accepted.connect(self.dlg_accept)
        dlg.rejected.connect(self.dlg_reject)
        dlg.finished.connect(self.dlg_finish)

        r = dlg.exec()
        print('exec return', r)
        self.pBar.setRange(0, 100000)
        for i in range(0, 100001):
            QApplication.processEvents()
            self.pBar.setValue(i)

    def open_dialog(self):
        print('******** open clicked *******')
        dlg = dlgForm(self)
        dlg.accepted.connect(self.dlg_accept)
        dlg.rejected.connect(self.dlg_reject)
        dlg.finished.connect(self.dlg_finish)

        r = dlg.open()
        print('open return', r)
        self.pBar.setRange(0, 100000)
        for i in range(0, 100001):
            QApplication.processEvents()
            self.pBar.setValue(i)

    def show_dialog(self):
        print('******** show clicked *******')
        dlg = dlgForm(self)

        dlg.setWindowModality(Qt.NonModal)
        # dlg.setWindowModality(Qt.WindowModal)
        # dlg.setWindowModality(Qt.ApplicationModal)

        dlg.accepted.connect(self.dlg_accept)
        dlg.rejected.connect(self.dlg_reject)
        dlg.finished.connect(self.dlg_finish)

        r = dlg.show()
        print('show return', r)
        self.pBar.setRange(0, 100000)
        for i in range(0, 100001):
            QApplication.processEvents()
            self.pBar.setValue(i)

    def dlg_accept(self):
        print('accepted')

    def dlg_reject(self):
        print('reject')

    def dlg_finish(self):
        print('finish')


class dlgForm(QDialog, Ui_Dialog):
    def __init__(self, parent=None, flag=Qt.Dialog):
        super().__init__(parent, flag)
        self.setupUi(self)
        self.btnOk.clicked.connect(self.accept)
        self.btnCancel.clicked.connect(self.reject)
        self.btnAccept.clicked.connect(self.dlg_accept)
        self.btnReject.clicked.connect(self.dlg_reject)
        self.btnDone.clicked.connect(self.dlg_done)

    def dlg_accept(self):
        self.accept()

    def dlg_reject(self):
        self.reject()
        self.setResult(20)

    def dlg_done(self):
        self.done(0)


if __name__ == '__main__':
    app = QApplication(sys.argv)
    w = Form()
    w.show()
    sys.exit(app.exec_())
