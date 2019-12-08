#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->timeEdit->setDisplayFormat("hh:mm:ss");
    playerTimer = new QMediaPlayer;
    playerAlarm = new QMediaPlayer;
    playerSecretBox = new QMediaPlayer;
    playerTimer->setMedia(QUrl("qrc:/sounds/recources/alarm-clock-beep.mp3"));
    playerAlarm->setMedia(QUrl("qrc:/sounds/recources/alarm-sound.mp3"));
    playerSecretBox->setMedia(QUrl("qrc:/sounds/recources/Secret-Box-Sound.mp3"));
    playerSecretBox->setVolume(50);
    playerAlarm->setVolume(50);
    QPixmap secretIcon(":/sounds/recources/secret-box-png.png");
    const int w = ui->secretBoxIcon->width();
    const int h = ui->secretBoxIcon->height();
    ui->secretBoxIcon->setPixmap(secretIcon.scaled(w, h, Qt::KeepAspectRatio));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_timer(const unsigned long long int &index)
{
    QListWidgetItem *selectedTimer = new QListWidgetItem;
    selectedTimer = ui->listWidget->item(index);
    int time = timersAndAlarmsList[index].timeMillSec();
    int i = 0;
    while(i != time) {
        i += 1000;
        timersAndAlarmsList[index].clock()->singleShot(i, this, [=](){
                selectedTimer->setText("Timer: " + QTime(0,0,0).addMSecs(time - i).toString() + timersAndAlarmsList[index].node());
                if(i == time) {
                    if(!ui->DisturbBox->isTristate()) {
                        playerTimer->play();
                        QMessageBox::warning(this, "KOPEC KONEC", "YOUR TIME ENDED", QMessageBox::Ok);
                        playerTimer->stop(); }
                    timersAndAlarmsList[index].clock()->stop();
                    selectedTimer->setText("Timer: " + QTime(0,0,0).addMSecs(time).toString() + timersAndAlarmsList[index].node());
                }
        });
    }
}

void MainWindow::update_alarm(const unsigned long long int &index) {
    int time = timersAndAlarmsList[index].timeMillSec();
    timersAndAlarmsList[index].clock()->singleShot(time, this, [=](){
       timersAndAlarmsList[index].clock()->stop();
       if(!ui->DisturbBox->isTristate()) {
           playerAlarm->play();
           QMessageBox::warning(this, "HEY", "WAKE UP!!!", QMessageBox::Ok);
           playerAlarm->stop(); }
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
    ui->statusbar->clearMessage();
    TimerAndAlarm newAlarm;
    newAlarm.Set_type(2);
    const int alarmtime = ui->timeEdit->time().msecsSinceStartOfDay();
    newAlarm.Set_timeMillSec(alarmtime);
    timersAndAlarmsList.push_back(newAlarm);
    QListWidgetItem *addAlarm = new QListWidgetItem;
    addAlarm->setText("Alarm: " + QTime(0,0,0).addMSecs(timersAndAlarmsList.back().timeMillSec()).toString());
    ui->listWidget->addItem(addAlarm);
}

void MainWindow::on_AddToGroupOfTimers_clicked()
{
    const unsigned long long int index = ui->listWidget->currentRow();
    if(timersAndAlarmsList[index].type() == isAlarm) { return; }
    timersAndAlarmsList[index].Set_node(" Group");
    QListWidgetItem *selectedTimer = new QListWidgetItem;
    selectedTimer = ui->listWidget->currentItem();
    selectedTimer->setText("Timer: " + QTime(0,0,0).addMSecs(timersAndAlarmsList[index].timeMillSec()).toString() + timersAndAlarmsList[index].node());
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

void MainWindow::on_StartGroup_clicked()
{
    if(timersAndAlarmsList.size() == 0) { QMessageBox::warning(this, "UPS", "Pls, add some timers to list.", QMessageBox::Ok); return; }
        else {
            for(unsigned long long int index = 0; index < timersAndAlarmsList.size(); ++index) {
                if(timersAndAlarmsList[index].node() == " Group") {
                    if(timersAndAlarmsList[index].clock()->isActive()) { continue; }
                    timersAndAlarmsList[index].clock()->start();
                    update_timer(index);
                }
            }
        }
}




void MainWindow::on_Delete_clicked()
{
    const int index = ui->listWidget->currentRow();
    if(timersAndAlarmsList[index].clock()->isActive()) {
        QMessageBox::warning(this, "UPS", "You cant delete object while it works", QMessageBox::Ok);
    } else {
        timersAndAlarmsList.erase(timersAndAlarmsList.begin() + index);
        ui->listWidget->takeItem(index);
    }
}

void MainWindow::on_DisturbBox_clicked(bool checked)
{
    if(checked) { ui->DisturbBox->setTristate(true); } else {
                  ui->DisturbBox->setTristate(false);
     }
}




void MainWindow::on_RemoveFromGroupOfTimers_clicked()
{
    const unsigned long long int index = ui->listWidget->currentRow();
    QListWidgetItem *selectedTimer = new QListWidgetItem;
    selectedTimer = ui->listWidget->currentItem();
    timersAndAlarmsList[index].Set_node("");
    selectedTimer->setText("Timer: " + QTime(0,0,0).addMSecs(timersAndAlarmsList[index].timeMillSec()).toString() + timersAndAlarmsList[index].node());
}

void MainWindow::on_SB_clicked()
{
    playerSecretBox->play();
    QMessageBox::warning(this,"WARNING!", "SECRET BOX!!!", QMessageBox::Ok);
    playerSecretBox->stop();
}
