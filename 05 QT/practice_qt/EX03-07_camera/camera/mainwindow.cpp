#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>

// ============================================================================
// MainWindow 생성자 (초기화 및 시작)
// ============================================================================
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this); // UI 디자이너 파일(*.ui)의 컴포넌트들을 화면에 배치 및 초기화

    // 1. 백그라운드에서 카메라를 구동할 스레드 객체 생성
    camera_thread = new CameraThread(this);
    
    // 2. 스레드(영상 송신)와 메인 UI(영상 수신)를 시그널-슬롯으로 연결
    connect(camera_thread, SIGNAL(send_image(const QImage&)),
            this, SLOT(handle_data(const QImage&)));

    // 3. 카메라 스레드 실행 (CameraThread::run() 함수가 호출됨)
    camera_thread->start();
}

// ============================================================================
// MainWindow 소멸자 (메모리 해제)
// ============================================================================
MainWindow::~MainWindow() {
    delete ui; // UI 동적 할당 메모리 해제
}

// ============================================================================
// 실시간 이미지 출력 슬롯 함수 (CameraThread에서 시그널을 보낼 때마다 실행)
// ============================================================================
void MainWindow::handle_data(const QImage &image) {
    // 1. 스레드로부터 받은 QImage를 화면 출력용 클래스인 QPixmap으로 변환
    QPixmap pixmap = QPixmap::fromImage(image);

    // 2. 영상을 출력할 라벨(lblImg)이 안전하게 존재한다면 이미지를 라벨에 셋팅
    if (ui->lblImg) {
        ui->lblImg->setPixmap(pixmap);
    }
}

// ============================================================================
// 윈도우 창 닫기 이벤트 핸들러 (X 버튼을 누르거나 프로그램을 종료할 때 실행)
// ============================================================================
void MainWindow::closeEvent(QCloseEvent *event) {
    // 카메라 스레드가 동작 중이라면 안전하게 종료 절차를 밟음
    if (camera_thread) {
        camera_thread->quit(); // 1. 스레드의 이벤트 루프(exec())를 빠져나오도록 종료 신호를 보냄
        camera_thread->wait(); // 2. 스레드가 완전히 종료(run() 함수가 완전히 끝날 때)될 때까지 메인 스레드가 대기
    }
    
    // 창 닫기 이벤트를 수락하여 프로그램을 최종적으로 종료시킴
    event->accept();
}