import sys
from PyQt5.QtCore import QThread, pyqtSignal, pyqtSlot
from PyQt5.QtMultimedia import QCamera, QCameraInfo, QAbstractVideoSurface, QVideoFrame
from PyQt5.QtGui import QImage

class VideoSurface(QAbstractVideoSurface):
    def __init__(self, callback, parent=None):
        super().__init__(parent)
        self.callback = callback

    def supportedPixelFormats(self, handleType):
        return [
            QVideoFrame.Format_RGB32,
            QVideoFrame.Format_ARGB32
        ]

    def present(self, frame):
        if frame.isValid():
            self.callback(frame)
        return True


class CameraThread(QThread):
    send_image = pyqtSignal(QImage)

    def __init__(self, parent=None):
        super().__init__(parent)
        self.camera = None
        self.video_surface = None
        self.frame_count = 0
        self.frame_divisor = 1

    def run(self):
        if self.init_capture() < 0:
            return

        if self.start_capture() < 0:
            return

        self.exec_()

        self.stop_capture()
        self.close_capture()

    def init_capture(self):
        if self.camera:
            return 0

        cameras = QCameraInfo.availableCameras()
        if not cameras:
            print("연결된 카메라 장치가 없습니다!")
            return -1

        print("=== 발견된 카메라 장치 목록 ===")
        for i, cam in enumerate(cameras):
            print(f"Index [{i}] : {cam.description()}")
        print("===============================")

        target_index = 1 if len(cameras) > 1 else 0
        print(f"현재 선택된 카메라: {cameras[target_index].description()}")

        self.camera = QCamera(cameras[target_index])
        self.video_surface = VideoSurface(self.process_video_frame)
        
        self.camera.setViewfinder(self.video_surface)
        return 0

    def process_video_frame(self, frame):
        if not frame.isValid():
            return

        clone_frame = QVideoFrame(frame)
        
        if clone_frame.map(1): # ReadOnly
            try:
                width = clone_frame.width()
                height = clone_frame.height()
                bytes_per_line = clone_frame.bytesPerLine()
                
                ptr = clone_frame.bits()
                
                if ptr is not None:
                    size = bytes_per_line * height
                    ptr.setsize(size)
                    
                    img = QImage(ptr, width, height, bytes_per_line, QImage.Format_RGB32)
                    
                    if not img.isNull():
                        self.frame_count += 1
                        if self.frame_count % self.frame_divisor == 0:
                            # 1. 표준 포맷으로 먼저 변환
                            standard_img = img.convertToFormat(QImage.Format_RGBA8888)
                            
                            # 2. 💡 상하 반전 적용 (첫 번째 인자 가로=False, 두 번째 인자 세로=True)
                            flipped_img = standard_img.mirrored(False, True)
                            
                            # 3. 반전된 이미지를 메인 윈도우로 전송
                            self.send_image.emit(flipped_img)
            except Exception as e:
                print(f"프레임 변환 중 오류 발생: {e}")
            finally:
                clone_frame.unmap()

    def start_capture(self):
        if self.camera:
            self.camera.start()
            print("PyQt5 QCamera Stream on...")
            return 0
        return -1

    def stop_capture(self):
        if self.camera:
            self.camera.stop()
            print("PyQt5 QCamera Stream off!!")
            return 0
        return -1

    def close_capture(self):
        self.camera = None
        self.video_surface = None