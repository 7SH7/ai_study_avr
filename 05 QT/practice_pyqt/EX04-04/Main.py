import sys
from PyQt5.QtWidgets import *

from PyQt5 import uic

form_class, base_class = uic.loadUiType('gui.ui')


class Form(base_class, form_class):
    def __init__(self):
        super().__init__()
        self.setupUi(self)


if __name__ == '__main__':
    app = QApplication(sys.argv)
    w = Form()
    w.show()
    sys.exit(app.exec_())
