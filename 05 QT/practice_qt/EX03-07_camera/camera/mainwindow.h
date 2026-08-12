#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QCloseEvent>
#include <QFileDialog>

#include "camerathread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void handle_data(const QImage &image);

    void on_btnCapture_clicked();

    void capture_image(bool isCapture);

signals:
    void send_capture_signal(bool isCapture);

private:
    Ui::MainWindow *ui;
    CameraThread *camera_thread;
    QImage current_image;
};
#endif // MAINWINDOW_H