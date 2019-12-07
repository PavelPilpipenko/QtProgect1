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

void MainWindow::update_timer(const unsigned long long int &index)
{
    QListWidgetItem *selectedTimer = new QListWidgetItem;
    selectedTimer = ui->listWidget->currentItem();
    int time = timersList[index].timeMillSec();
    int i = 0;
    while(i != time) {
        i += 1000;
        timersList[index].ttimer()->singleShot(i, this, [=](){
                selectedTimer->setText("Timer: " + QTime(0,0,0).addMSecs(time - i).toString());
                if(i == time) {
                   QMessageBox::warning(this, "VSE", "YOUR TIME ENDED", QMessageBox::Ok);
                   timersList[index].ttimer()->stop();
                   selectedTimer->setText("Timer: " + QTime(0,0,0).addMSecs(time).toString());
                }
               });
    }
}

void MainWindow::on_addTimerBurron_clicked()
{
    Timer newTimer;
    if(ui->timeEdit->time().msecsSinceStartOfDay() == 0) {
        ui->statusbar->showMessage("Invalid time");
        return;
    }
    ui->statusbar->clearMessage();
    newTimer.Set_timeMillSec(ui->timeEdit->time().msecsSinceStartOfDay());
    timersList.push_back(newTimer);
    QListWidgetItem *addTimer = new QListWidgetItem;
    addTimer->setText("Timer: " + QTime(0,0,0).addMSecs(timersList.back().timeMillSec()).toString());
    ui->listWidget->addItem(addTimer);
}

void MainWindow::on_start_clicked()
{
    const unsigned long long int index = ui->listWidget->currentRow();
    timersList[index].ttimer()->start();
    update_timer(index);
}





void MainWindow::on_Delete_clicked()
{
    const int index = ui->listWidget->currentRow();
    if(timersList[index].ttimer()->isActive()) {
        QMessageBox::warning(this, "UPS", "You cant delete timer while it works", QMessageBox::Ok);
    } else {
        timersList[index].ttimer()->stop();
        timersList.erase(timersList.begin() + index);
        ui->listWidget->takeItem(index);
    }
}
