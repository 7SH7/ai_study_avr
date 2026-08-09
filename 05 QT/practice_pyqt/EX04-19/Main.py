import sys, os, subprocess
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from mythread import MyThread
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
        self.myThread = MyThread()
        self.toggle = 0
        self.myThread.send_command.connect(self.handle_command)
        self.btnStart.clicked.connect(self.start_click)
        self.btnStop.clicked.connect(self.stop_click)
        
    def handle_command(self, cmd):
        print(f"handle_command {cmd}")
        if cmd == 1:
            self.toggle ^= 1
            
            if self.toggle:
                self.lblRedLed.setStyleSheet("background-color: red")
            else:
                self.lblRedLed.setStyleSheet("background-color: black")

    def start_click(self):
        print('start')
        if self.myThread.is_running():
            print('already started')
            return
        self.myThread.start()

    def stop_click(self):
        print('stop')
        self.myThread.stop()
if __name__ == '__main__':
    app = QApplication(sys.argv)
    w = Form()
    w.show()
    sys.exit(app.exec())
