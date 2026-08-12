#include "mythread.h"

MyThread::MyThread(QObject *parent)
    : QThread{parent}
{
    running = false;
}

void MyThread::run(){
    int cnt = 0;
    running = true; // thread 돌아

    while(running == true){ // thread가 돌고 있으면..!
        msleep(100);        // 100ms동안 기다려
        if(cnt++ == 10){    // 10만큼 >> 1000ms 기다려
            cnt = 0;
            emit send_command(1);   // 다 기다렸으면, 다 기다렸어~ 라고 띄우기
        }
    }
}

void MyThread::stop(){
    running = false;
}

bool MyThread::is_running(){
    return running;
}