import sys ,subprocess
from PyQt5.QtWidgets import QApplication, QMainWindow
from PyQt5.QtGui import QPixmap, QImage
from PyQt5.QtCore import pyqtSlot
GUI_FILE_NAME = 'gui'
subprocess.run([
    sys.executable,          
    '-m', 'PyQt5.uic.pyuic', 
    '-x', f'{GUI_FILE_NAME}.ui', 
    '-o', f'{GUI_FILE_NAME}.py'
])
from gui import Ui_MainWindow
from Thread import CameraThread
class Form(QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        
        # 스레드 생성 및 신형 스타일 connect 연결
        self.camera_thread = CameraThread(self)
        self.camera_thread.send_image.connect(self.handle_data)

        # 카메라 스레드 스타트
        self.camera_thread.start()

    @pyqtSlot(QImage)
    def handle_data(self, image):
        # 스레드가 완벽하게 빌드해서 던져준 이미지이므로 찢어짐 없이 바로 Pixmap 전환 출력!
        pixmap = QPixmap.fromImage(image)
        self.lblImg.setPixmap(pixmap)

    def closeEvent(self, event):
        # 윈도우가 닫힐 때 스레드를 안전하게 종료시킵니다.
        self.camera_thread.quit()
        self.camera_thread.wait()
        event.accept()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    w = Form()
    w.show()
    sys.exit(app.exec())