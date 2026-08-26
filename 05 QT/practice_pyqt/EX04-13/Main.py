import sys ,subprocess

from PyQt5.QtWidgets import QFileDialog, QMainWindow, QApplication
from PyQt5.QtCore import QFileInfo

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
        self.pushButton.clicked.connect(self.open_file)
        self.pushButton_2.clicked.connect(self.save_file)

    def open_file(self):
        # filepath = QFileDialog.getExistingDirectory(self, 
        #     "Select Directory", 
        #     r"C:\Users\kccistc\Desktop\ai_study_avr\05 QT\practice_pyqt"r"\Users\kccistc\Desktop\ai_study_avr\05 QT\practice_pyqt"
        # )
        filter = "모든파일(*.*);이미지파일(.jpg);텍스트파일(.txt);파이썬파일(*.py)"
        filepath, _ = QFileDialog.getOpenFileName(filter=filter, initialFilter="모든파일(*.*)")
        self.label.setText(filepath)
    
    def save_file(self):
        filepath = QFileDialog.getSaveFileName(self, 
                "Select Directory", 
                r"C:\Users\kccistc\Desktop\ai_study_avr\05 QT\practice_pyqt"r"\Users\kccistc\Desktop\ai_study_avr\05 QT\practice_pyqt",
                "Text Files (*.txt);;All Files (*)"
            )
        self.label_2.setText(filepath)
        
if __name__ == '__main__':
    app = QApplication(sys.argv)
    w = Form()
    w.show()
    sys.exit(app.exec_())
