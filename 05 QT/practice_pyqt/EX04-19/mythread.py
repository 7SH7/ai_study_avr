from PyQt5.QtCore import QThread, pyqtSignal

class MyThread(QThread):
    send_command = pyqtSignal(int)

    def __init__(self):
        super().__init__()
        self.running = False
    # 다음 메서드를 작성하라
    def run(self):
        pass

    # 다음 메서드를 작성하라
    def stop(self):
        pass
    # 다음 메서드를 작성하라
    def is_running(self):
        pass