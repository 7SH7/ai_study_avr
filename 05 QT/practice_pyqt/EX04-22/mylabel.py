from PyQt5.QtWidgets import QLabel
from PyQt5.QtGui import QPixmap
from PyQt5.QtCore import Qt, QFileInfo

import os

# class mylabel(QLabel):
#     def __init__(self, parent = None):
#         super.__init__(parent)
#         self.setAcceptDrops(True)
#         self.setScaledContents(True)

#     def getImagePath(self, mimeData):
#         if mimeData.hasUrls():  # drag된 data에 파일 없음
#             return ""
#         filepath = mimeData.urls()[0].toLocalFile()
#         # os.path.splitext(filepath)[1].lower().lstrip
        
#         ext = QFileInfo(filepath).suffix.toLower()
#         if ext == 'png' or ext == 'jpg' or ext == 'bmp':
#             return filepath
#         else:
#             return ""

#     def dragEnterEvent(self, e):
#         if self.getImagePath(e.mimeData()) != "":
#             e.accept()
#         else:
#             e.ignore()

#     def dropEvent(self, e):
#         filepath = self.getImagePath(e.mimeData())
#         if filepath != "":
#             pixmap = QPixmap(filepath)
#             self.setPixmap()
#             e.accept()
            

class MyLabel(QLabel):
    def getImagePath(self, mimeData): 
        if not mimeData.hasUrls(): 
            return ""
            #파일경로 획득.. 1개만 드롭
        filepath = mimeData.urls()[0].toLocalFile() #확장자 체크
        ext = QFileInfo(filepath). suffix().lower()
        if ext== 'png' or ext == 'jpg' or ext == 'bmp':
            return filepath
        else:
            return ""

    def dragEnterEvent (self, e):
        if self.getImagePath(e.mimeData()) !="":
            e.accept()
        else:
            e.ignore()

    def dropEvent (self, e):
        filepath = self.getImagePath(e.mimeData()) 
        if filepath == "":
            pixmap =QPixmap (filepath)
            self.setPixmap(pixmap)
            e.accept()