import sys ,subprocess

from PyQt5.QtWidgets import QMainWindow, QApplication
from PyQt5.QtCore import QTimer, QTime

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
        # timer basic code
        self.tick = 0
        self.timer = QTimer(self);
        self.timer.timeout.connect(self.timeTick);
        self.timer.start(1000)
        # ui intialization
        self.lblRed.setStyleSheet("background-color:red")
        self.lblGreen.setStyleSheet("background-color:green")
        timestr = QTime.currentTime().toString("HH:mm:ss")
        self.lcdNumber.display(timestr)

    def timeTick(self):
        if(self.tick==1):
            self.lblRed.setStyleSheet("background-color: red")
            self.lblGreen.setStyleSheet("background-color: green")
            self.tick= 0
            self.lcdNumber.display(QTime.currentTime().toString("HH:mm:ss"))

        else:
            self.lblRed.setStyleSheet("background-color: green")
            self.lblGreen.setStyleSheet("background-color: red")
            self.tick = 1
            self.lcdNumber.display(QTime.currentTime().toString("HH:mm:ss"))

if __name__ == '__main__':
    app = QApplication(sys.argv)
    w = Form()
    w.show()
    sys.exit(app.exec_())
