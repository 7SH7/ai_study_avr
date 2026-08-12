import sys, subprocess, os
from PyQt5.QtWidgets import QMainWindow, QApplication

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
        self.check_clicked = 0
        self.pushButton_3.clicked.connect(self.chgframe1)

        self.pushButton_2.setCheckable(True)
        self.pushButton_2.toggled.connect(self.chgframe2)

    def chgframe1(self):
        if(self.check_clicked == 0):
            self.label.setStyleSheet("border: 2px solid red;")
            self.check_clicked = 1
        elif(self.check_clicked == 1):
            self.label.setStyleSheet("border: 2px solid green;")
            self.check_clicked = 2
        elif(self.check_clicked == 2):
            self.label.setStyleSheet("border: 2px solid blue;")
            self.check_clicked = 0
                    


    def chgframe2(self, toggled):
        if(toggled):
            self.label_2.setStyleSheet("border: 2px solid green;")
        else:
            self.label_2.setStyleSheet("border: 2px solid red;")
        



if __name__ == '__main__':
    app = QApplication(sys.argv)
    w = Form()
    w.show()
    sys.exit(app.exec_())
