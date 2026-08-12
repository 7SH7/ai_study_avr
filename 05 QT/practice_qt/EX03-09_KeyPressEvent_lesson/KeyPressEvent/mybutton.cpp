#include "mybutton.h"

MyButton::MyButton(QWidget *parent) : QPushButton(parent)
{
    setStyleSheet("background-color:yellow;");
}

void MyButton::mousePressEvent(QMouseEvent *e){
    setStyleSheet("background-color:red;");
    QPushButton::mousePressEvent(e);
    click_count++;
}

void MyButton::mouseReleaseEvent(QMouseEvent *e){
    setStyleSheet("background-color:green;");
    QPushButton::mouseReleaseEvent(e);  // 이거 필수
}

int MyButton::clickcount(){
    return click_count;
}