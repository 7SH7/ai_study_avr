import sys ,subprocess

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
        # 시그널 슬롯 연결: 송신자.시그널.coonect(수신자.슬롯함수명)
        # self.pushButton.clicked.connect(lambda: self.label.setText("Hello"))
        self.pushButton.clicked.connect(self.Hello);
        self.pushButton_2.clicked.connect(lambda: self.label.setText("World"))

    def Hello(self):
        self.label.setText("Hello")

        


if __name__ == '__main__':
    app = QApplication(sys.argv)
    w = Form()
    w.show()
    sys.exit(app.exec_())
