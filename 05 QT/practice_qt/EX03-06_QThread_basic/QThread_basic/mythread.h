#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);

    void run();
    void stop();
    bool is_running();

private:
    volatile bool running;

signals:
    void send_command(int cmd);

};

#endif // MYTHREAD_H
