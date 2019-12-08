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
    int time = timersAndAlarmsList[index].timeMillSec();
    int i = 0;
    while(i != time) {
        i += 1000;
        timersAndAlarmsList[index].clock()->singleShot(i, this, [=](){
                selectedTimer->setText("Timer: " + QTime(0,0,0).addMSecs(time - i).toString());
                if(i == time) {
                   QMessageBox::warning(this, "KOPEC KONEC", "YOUR TIME ENDED", QMessageBox::Ok);
                   timersAndAlarmsList[index].clock()->stop();
                   selectedTimer->setText("Timer: " + QTime(0,0,0).addMSecs(time).toString());
                }
               });
    }
}

void MainWindow::update_alarm(const unsigned long long int &index) {
    int time = timersAndAlarmsList[index].timeMillSec();
    timersAndAlarmsList[index].clock()->singleShot(time, this, [=](){
       QMessageBox::warning(this, "HEY", "WAKE UP!!!", QMessageBox::Ok);
       timersAndAlarmsList[index].clock()->stop();
    });
}

void MainWindow::on_addTimerButton_clicked()
{
    TimerAndAlarm newTimer;
    newTimer.Set_type(1);
    if(ui->timeEdit->time().msecsSinceStartOfDay() == 0) {
        ui->statusbar->showMessage("Invalid time");
        return;
    }
    ui->statusbar->clearMessage();
    newTimer.Set_timeMillSec(ui->timeEdit->time().msecsSinceStartOfDay());
    timersAndAlarmsList.push_back(newTimer);
    QListWidgetItem *addTimer = new QListWidgetItem;
    addTimer->setText("Timer: " + QTime(0,0,0).addMSecs(timersAndAlarmsList.back().timeMillSec()).toString());
    ui->listWidget->addItem(addTimer);
}

void MainWindow::on_addAlarmButton_clicked()
{
    TimerAndAlarm newAlarm;
    newAlarm.Set_type(2);
    const int alarmtime = ui->timeEdit->time().msecsSinceStartOfDay();
    newAlarm.Set_timeMillSec(alarmtime);
    timersAndAlarmsList.push_back(newAlarm);
    QListWidgetItem *addAlarm = new QListWidgetItem;
    addAlarm->setText("Alarm" + QTime(0,0,0).addMSecs(timersAndAlarmsList.back().timeMillSec()).toString());
    ui->listWidget->addItem(addAlarm);
}

void MainWindow::on_start_clicked()
{
    const unsigned long long int index = ui->listWidget->currentRow();
    if(timersAndAlarmsList[index].clock()->isActive()) { return; }
    if(timersAndAlarmsList[index].type() == isTimer) {
        timersAndAlarmsList[index].clock()->start();
        update_timer(index);
    } else if(timersAndAlarmsList[index].type() == isAlarm) {
        const int currTimeMillSec = QTime(0,0,0).currentTime().second()*1000 + QTime(0,0,0).currentTime().minute()*60000 + QTime(0,0,0).currentTime().hour()*3600000;
        int time;
        if(currTimeMillSec > timersAndAlarmsList[index].timeMillSec()) {
            time = 24*3600000 - (currTimeMillSec - timersAndAlarmsList[index].timeMillSec());
        } else {
            time= timersAndAlarmsList[index].timeMillSec() - currTimeMillSec;
        }
        timersAndAlarmsList[index].Set_timeMillSec(time);
        timersAndAlarmsList[index].clock()->start();
        update_alarm(index);
    }
}





void MainWindow::on_Delete_clicked()
{
    const int index = ui->listWidget->currentRow();
    if(timersAndAlarmsList[index].clock()->isActive()) {
        QMessageBox::warning(this, "UPS", "You cant delete timer while it works", QMessageBox::Ok);
    } else {
        timersAndAlarmsList.erase(timersAndAlarmsList.begin() + index);
        ui->listWidget->takeItem(index);
    }
}


