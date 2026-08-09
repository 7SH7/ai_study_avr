import sys, subprocess
from PyQt5.QtWidgets import *

GUI_FILE_NAME = 'gui'
subprocess.run([
    sys.executable,          
    '-m', 'PyQt5.uic.pyuic', 
    '-x', f'{GUI_FILE_NAME}.ui', 
    '-o', f'{GUI_FILE_NAME}.py'
])
from gui import Ui_MainWindow


class Form(QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()

        self.setupUi(self)
        self.btnCritical.clicked.connect(self.critical)

        self.btnInfo.clicked.connect(self.information)
        self.btnQuestion.clicked.connect(self.question)
        self.btnWarning.clicked.connect(self.warning)

    def critical(self):
        QMessageBox.critical(self, 'critical', 'critical message')
    
    def information(self):
        QMessageBox.information(self, 'information', 'infomation message',
                                                             QMessageBox.Ok | QMessageBox.Cancel)
    def question(self):
        r = QMessageBox.question(self, 'question', 'question message', QMessageBox.Yes | QMessageBox.No)
        print(r)
        if r == QMessageBox.Yes:
            print('YES')
        else:
            print('NO')
    def warning(self):
         QMessageBox.warning(self, 'warning', 'warning message',
                                                            QMessageBox.Retry | QMessageBox.Ignore)
if __name__ == '__main__':
    app = QApplication(sys.argv)
    w = Form()
    w.show()
    sys.exit(app.exec_())
