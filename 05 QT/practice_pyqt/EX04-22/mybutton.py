from PyQt5.QtWidgets import QPushButton

class myButton(QPushButton):
    def __init__(self, parent = None):
        super().__init__(parent)
        self.cnt = 0
        self.setStyleSheet("background-color: yellow")

    def mousePressEvent(self, e):
        self.setStyleSheet("background-color: red")
        self.cnt+=1
        QPushButton.mousePressEvent(self, e)

    def mouseReleaseEvent(self, e):
        self.setStyleSheet("background-color: green")
        super().mouseReleaseEvent(e)    # super(). 으로 하면, super가 자동으로 첫번째 인자로 넘어가니까
    
    def get_count(self):
        return self.cnt
    
        