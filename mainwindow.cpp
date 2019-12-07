#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->timeEdit->setDisplayFormat("hh:mm:ss");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_timer()
{
    QListWidgetItem *selectedTimer = new QListWidgetItem;

    unsigned long long int index = ui->listWidget->currentRow();
    selectedTimer = ui->listWidget->currentItem();
    int time = timersListTime[index];
    int i = 0;
    while(i != time) {
        i += 1000;
        timer->singleShot(i, this, [=](){
            selectedTimer->setText("Timer: " + QTime(0,0,0).addMSecs(time - i).toString());
            if(i == time) {
                QMessageBox::warning(this, "VSE", "YOUR TIME ENDED", QMessageBox::Ok);
                selectedTimer->setText("Timer: " + QTime(0,0,0).addMSecs(time).toString());
            }
        });
    }
}

void MainWindow::on_addTimerBurron_clicked()
{
    if(ui->timeEdit->time().msecsSinceStartOfDay() == 0) {
        ui->statusbar->showMessage("Invalid time");
        return;
    }
    ui->statusbar->clearMessage();
    Set_timeMillSec(ui->timeEdit->time().msecsSinceStartOfDay());
    timersListTime.push_back(ui->timeEdit->time().msecsSinceStartOfDay());
    QListWidgetItem *addTimer = new QListWidgetItem;
    addTimer->setText("Timer: " + QTime(0,0,0).addMSecs(timersListTime.back()).toString());
    ui->listWidget->addItem(addTimer);
}

void MainWindow::on_start_clicked()
{
    timer->start();
    update_timer();
}
