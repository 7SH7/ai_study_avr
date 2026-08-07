# if 0

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_chkTri_stateChanged(int arg1)
{
    qDebug() << "state changed" << arg1;
    qDebug() << "checkState()" << ui->chkTri->checkState();
}

void MainWindow::on_chkTri_toggled(bool checked)
{
    qDebug() << "toggled" << checked;
    qDebug() << "isChecked()" << ui->chkTri->isChecked();
}

void MainWindow::on_chkC_stateChanged(int arg1)
{
    process_stateChanged(arg1, ui->chkC);
}

void MainWindow::process_stateChanged(int checked, QCheckBox *chk)
{
    qDebug() << checked << " " << chk->text();
}

void MainWindow::on_chkCpp_stateChanged(int arg1)
{
    process_stateChanged(arg1, ui->chkCpp);
}


void MainWindow::on_chkJava_stateChanged(int arg1)
{
    process_stateChanged(arg1, ui->chkJava);
}


void MainWindow::on_chkPython_stateChanged(int arg1)
{
    process_stateChanged(arg1, ui->chkPython);
}

# endif

#if 0

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // cpp 람다 [캡쳐] (파라미터) 함수 내용}
    // 캡쳐: 변수를 가져다가 사용함을 명시해주는 것

    connect(ui->chkC, &QCheckBox::stateChanged, this,
            [this](bool st){process_stateChanged(st, ui->chkC);});
    connect(ui->chkCpp, &QCheckBox::stateChanged, this,
            [this](bool st){process_stateChanged(st, ui->chkCpp);});
    connect(ui->chkJava, &QCheckBox::stateChanged, this,
            [this](bool st){process_stateChanged(st, ui->chkJava);});
    connect(ui->chkPython, &QCheckBox::stateChanged, this,
            [this](bool st){process_stateChanged(st, ui->chkPython);});
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_chkTri_stateChanged(int arg1)
{
    qDebug() << "state changed" << arg1;
    qDebug() << "checkState()" << ui->chkTri->checkState();
}

void MainWindow::on_chkTri_toggled(bool checked)
{
    qDebug() << "toggled" << checked;
    qDebug() << "isChecked()" << ui->chkTri->isChecked();
}

void MainWindow::on_chkC_stateChanged(int arg1)
{
    process_stateChanged(arg1, ui->chkC);
}

void MainWindow::process_stateChanged(int checked, QCheckBox *chk)
{
    static QStringList lst;
    QString msg;

    qDebug() << checked << " " << chk->text();
    if(checked == 2) lst.append(chk->text());
    else if(checked == 0) lst.removeOne(chk->text());

    if(lst.empty()){
        msg = "I have no language available";
    } else {
        lst.sort();
        msg = "I can use " + lst.join(" ");
    }

    ui->lblMsg->setText(msg);
}

void MainWindow::on_chkCpp_stateChanged(int arg1)
{
    process_stateChanged(arg1, ui->chkCpp);
}


void MainWindow::on_chkJava_stateChanged(int arg1)
{
    process_stateChanged(arg1, ui->chkJava);
}


void MainWindow::on_chkPython_stateChanged(int arg1)
{
    process_stateChanged(arg1, ui->chkPython);
}

#endif


#if 1

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // cpp 람다 [캡쳐](파라메터){함수 내용}
    // connect(ui->chkC, &QCheckBox::stateChanged, this,
    //         [this](int st){process_stateChanged(st, ui->chkC);});
    // connect(ui->chkCpp, &QCheckBox::stateChanged, this,
    //         [this](int st){process_stateChanged(st, ui->chkCpp);});
    // connect(ui->chkJava, &QCheckBox::stateChanged, this,
    //         [this](int st){process_stateChanged(st, ui->chkJava);});
    // connect(ui->chkPython, &QCheckBox::stateChanged, this,
    //         [this](int st){process_stateChanged(st, ui->chkPython);});

    // change to buttonGroup

    connect(ui->buttonGroup,
            // &QButtonGroup::buttonToggled, -> buttonToggled가 2개 있음(오버로드) > 어떤 것을 사용해야하는지 불분명
            qOverload<QAbstractButton *, bool>(&QButtonGroup::buttonToggled),   // 이것도 되고, 뒤도 가능
            // QOverload<QAbstractButton *, bool>::of(&QButtonGroup::buttonToggled),
            this,
            &MainWindow::Use_Lang);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_chkTri_stateChanged(int arg1)
{
    qDebug() << "state changed" << arg1;
    qDebug() << "checkState()" << ui->chkTri->checkState();
}


void MainWindow::on_chkTri_toggled(bool checked)
{
    qDebug() << "toggled" << checked;
    qDebug() << "isCheked()" << ui->chkTri->isChecked();
}

void MainWindow::Use_Lang(QAbstractButton *chk, bool checked)
{
    static QStringList list;
    QString msg;
    if(checked){
        list.append(chk->text());
    }
    else{
        list.removeOne(chk->text());
    }

    if(list.empty()){
        msg =  "I have no language availble";
    }
    else{
        list.sort();
        msg = "I can use " + list.join(" ");
    }
    ui->lblMsg->setText(msg);
}

void MainWindow::process_stateChanged(int checked, QCheckBox *chk)
{
    static QStringList list;
    QString msg;
    if(checked){
        list.append(chk->text());
    }
    else{
        list.removeOne(chk->text());
    }

    if(list.empty()){
        msg =  "I have no language availble";
    }
    else{
        list.sort();
        msg = "I can use " + list.join(" ");
    }
    ui->lblMsg->setText(msg);
}

// void MainWindow::on_chkC_stateChanged(int arg1)
// {
//     process_stateChanged(arg1, ui->chkC);
// }


// void MainWindow::on_chkCpp_stateChanged(int arg1)
// {
//     process_stateChanged(arg1,  ui->chkCpp);
// }


// void MainWindow::on_chkJava_stateChanged(int arg1)
// {
//     process_stateChanged(arg1,  ui->chkJava);
// }


// void MainWindow::on_chkPython_stateChanged(int arg1)
// {
//     process_stateChanged(arg1,  ui->chkPython);
// }


#endif