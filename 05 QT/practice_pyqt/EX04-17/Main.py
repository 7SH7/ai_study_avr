import sys, os, subprocess
from PyQt5.QtWidgets import *
from PyQt5.QtCore import Qt

MAIN_FILE_NAME = 'main_wnd'
DIALOG_FILE_NAME = 'dialog'

subprocess.run([
    sys.executable,          
    '-m', 'PyQt5.uic.pyuic', 
    '-x', f'{MAIN_FILE_NAME}.ui', 
    '-o', f'{MAIN_FILE_NAME}.py'
])
subprocess.run([
    sys.executable,          
    '-m', 'PyQt5.uic.pyuic', 
    '-x', f'{DIALOG_FILE_NAME}.ui', 
    '-o', f'{DIALOG_FILE_NAME}.py'
])
from main_wnd import Ui_MainWindow
from dialog import Ui_Dialog


class Form(QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.actionHobby.triggered.connect(self.show_dialog)

    def show_dialog(self):
        # todo : dlgForm 객체를 생성하여 이름을 넘겨주어 객체 생성
        dlg = dlgForm(self, name=self.editName.text()) # Todo : 생성자 수정

        dlg.accepted.connect(lambda: self.print_info(dlg.getInfo()))
        dlg.open()

    def print_info(self, tinfo):
        # Todo : 다이얼로그에서 넘겨 받은 tinfo를 main window에 표시
        nick, hobby, gender = tinfo
        self.lblNick.setText(f'닉네임 : {nick if nick else "없음"}')
        self.lblGender.setText(f'성별 : {gender if gender else "미공개"}')
        self.lblHobby.setText(f'취미: {','.join(hobby)}')


class dlgForm(QDialog, Ui_Dialog):

    def __init__(self, parent=None, flag=Qt.Dialog, name=None):
        super().__init__(parent, flag)
        self.setupUi(self)
        # Todo :  넘어온 name를 line edit에 표시
        self.editNick.setText(name);

    def getNick(self):
        # Todo : 닉네임 리턴
        nick_name = self.editNick.text()

        print(nick_name)
        
        return nick_name

    def getHobby(self):
        # Todo : 선택된 취미를 list로 만들어 리턴
        lst_hobby = []

        hobby1_chk, hobby2_chk, hobby3_chk = self.buttonGroup.buttons()
        if hobby1_chk.isChecked() == True:
            lst_hobby.append(self.chkHobby1.text())
        if hobby2_chk.isChecked() == True:
            lst_hobby.append(self.chkHobby2.text()) 
        if hobby3_chk.isChecked() == True:
            lst_hobby.append(self.chkHobby3.text())

        # for chk in self.buttonGroup.buttons():
        #   if(chk.isChecked()):
        #       lst_hobby.append(chk.text())

        print(lst_hobby)
        print("buttonGroup.buttons : " , self.buttonGroup.buttons()[0])
        print("checked : " , self.chkHobby1.isChecked)     # isChecked 요소가 check되어있나 확인하는 것: isChecked()
        
        return lst_hobby

    def getGender(self):
        # Todo : 선택된 성별을 문자열로 리턴
        if(self.rdoFemale.isChecked()):
            gender = "여성"
        else:
            gender = "남성"

        print(gender)

        return gender

    def getInfo(self):
        r = self.getNick(), self.getHobby(), self.getGender()
        print(r)
        return r


if __name__ == '__main__':
    app = QApplication(sys.argv)
    w = Form()
    w.show()
    sys.exit(app.exec_())
