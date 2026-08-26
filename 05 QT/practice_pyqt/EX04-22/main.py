import sys, os, subprocess
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import Qt
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
        self.pos_x = 40
        self.pos_y = 40
        self.move_block(0,0)
        self.pushButton.clicked.connect(lambda: print("button 1"))

    # 다음을 작성하시오.
    def keyPressEvent(self, event):
        key_map = {
            Qt.Key_Up: (0, -20),
            Qt.Key_Down: (0, 20),
            Qt.Key_Left: (-20, 0),
            Qt.Key_Right: (20, 0)
        }
        # dx, dy = key_map[event.key()]
        dx, dy = key_map.get(event.key(), (0, 0))
        self.move_block(dx, dy) # 없는 키 눌리면 에러

    # 다음을 작성하시오.
    def move_block(self, inc_x, inc_y):
        max_x = self.width() - self.lblBlock.width()
        max_y = self.height() - self.lblBlock.height()
        new_x, new_y = self.pos_x + inc_x, self.pos_y + inc_y

        self.pos_x = max(0, min(new_x, max_x))
        self.pos_y = max(0, min(new_y, max_y))

        self.lblBlock.move(self.pos_x, self.pos_y)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    w = Form()
    w.show()
    sys.exit(app.exec())
