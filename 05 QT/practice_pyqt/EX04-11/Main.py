import sys ,subprocess, QMessageBox

from PyQt5.QtWidgets import QMainWindow, QApplication

GUI_FILE_NAME = 'gui'
subprocess.run([
    sys.executable,          
    '-m', 'PyQt5.uic.pyuic', 
    '-x', f'{GUI_FILE_NAME}.ui', 
    '-o', f'{GUI_FILE_NAME}.py'
])
from gui import Ui_MainWindow


# try catch 하나 추가!
class Form(QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.oper_arr = ""

        self.btnGroupDisp.buttonClicked.connect(self.input_num)
        self.btnC.clicked.connect(self.input_clear)
        self.btnBack.clicked.connect(self.input_back)
        self.btnResult.clicked.connect(self.print_result)

    # 밑의 3개를 한번에 묶어서 처리 가능 >> btn == self.btnBack 이런 식
    def print_result(self):
        result = eval(self.oper_arr)
        self.oper_arr = '0';
        self.lblDisp.setText(str(result))

    def input_back(self):
        tmp = self.oper_arr[0 : len(self.oper_arr) - 1]  # 문법 체크!
        self.oper_arr = tmp
        self.lblDisp.setText(self.oper_arr)

    def input_num(self, btn):
        if(self.oper_arr == '0'):
            self.oper_arr = btn.text();
            self.lblDisp.setText(self.oper_arr)
        else:
            self.oper_arr += (btn.text())
            self.lblDisp.setText(self.oper_arr)

    def input_clear(self):
        self.oper_arr = '0';
        self.lblDisp.setText(self.oper_arr)



if __name__ == '__main__':
    app = QApplication(sys.argv)
    w = Form()
    w.show()
    sys.exit(app.exec_())
