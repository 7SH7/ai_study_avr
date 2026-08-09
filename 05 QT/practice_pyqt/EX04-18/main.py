import sys ,subprocess, os
from PyQt5.QtWidgets import QApplication, QMainWindow, QDialog
from PyQt5.QtCore import pyqtSlot, pyqtSignal

gui_files = ['gui','dlg']
for file_name in gui_files:
    subprocess.run([
        sys.executable,          
        '-m', 'PyQt5.uic.pyuic', 
        '-x', f'{file_name}.ui', 
        '-o', f'{file_name}.py'
    ])
from gui import Ui_MainWindow
from dlg import Ui_MyDialog

class Form(QMainWindow, Ui_MainWindow):
    # Todo : Form 사용자 시그널 생성 Main->Dialog
    
    def __init__(self):
        super().__init__()
        self.dlg = Dlg(self)
        self.setupUi(self)
        self.btnEdit.clicked.connect(self.openDlg)
        # Todo : 사용자 시그널 연결
        # Form에서 발생시그널 -> Dialog 슬롯
        # Dialog 시그널 -> Form 슬롯
        
    def receive_hobby(self, hobby):
        self.lblHobby.setText(f'Hobby: {hobby}')
    def openDlg(self):
        # Todo : Form 사용자 시그널 방출
        self.dlg.open()

class Dlg(QDialog, Ui_MyDialog):
    # Todo : Dialog 사용자 시그널 생성 Dialog->Main
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setupUi(self)
        self.btnOK.clicked.connect(self.okClick)
    def receive_name(self,name):
        self.lblName.setText(name)

    def okClick(self):
        l = []
        if self.chkFishing.isChecked():l.append('Fishig')
        if self.chkSurfing.isChecked():l.append('Surfing')
        if self.chkTraveling.isChecked():l.append('Traveling')
        # Todo : Dialog 사용자 시그널 방출
        
        self.accept()
if __name__ == '__main__':
    app = QApplication(sys.argv)
    w = Form()
    w.show()
    sys.exit(app.exec())
