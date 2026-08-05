import sys
from PyQt5.QtWidgets import *

if __name__ == '__main__':

    app = QApplication(sys.argv)

    w = QWidget()
    w.setGeometry(100,100,200,50)
    w.setWindowTitle('PyQT')

    label = QLabel(w)
    label.setText("Hello World")
    label.move(50,20)
    w.show()

    sys.exit(app.exec_())



