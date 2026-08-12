#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
private:
    int click_count = 0;

public:
    MyButton(QWidget *parent = nullptr);
    int clickcount();

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

};

#endif // MYBUTTON_H
