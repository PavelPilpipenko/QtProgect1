#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->timeEdit->setDisplayFormat("hh:mm:ss");
    group = " Group 1";
    clickSound = true;
    doubleclick = false;
    offButtons();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::offButtons() {
    ui->AddToGroupOfTimers->setEnabled(false);
    ui->RemoveFromGroupOfTimers->setEnabled(false);
    ui->start->setEnabled(false);
    ui->Delete->setEnabled(false);
    ui->StartGroup->setEnabled(false);
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
                        QMessageBox::warning(this, "Timer", "Time ended.", QMessageBox::Ok);
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
           QMessageBox::warning(this, "Alarm clock", "Wake up.", QMessageBox::Ok);
           playerAlarm->stop(); }
    });
}

//UI:
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
        timersAndAlarmsList[index].Set_node(group);
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
        unsigned long long int index = ui->listWidget->currentRow();
        const QString changedGroup = timersAndAlarmsList[index].node();
        if(changedGroup == "") { return; }
            for(index = 0; index < timersAndAlarmsList.size(); ++index) {
                if(timersAndAlarmsList[index].node() == changedGroup) {
                    if(timersAndAlarmsList[index].clock()->isActive()) { continue; }
                    timersAndAlarmsList[index].clock()->start();
                    update_timer(index);
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
        if(timersAndAlarmsList.size() == 0) {
            offButtons();
        }
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
        if(timersAndAlarmsList[index].type() == isAlarm) { return; }
        QListWidgetItem *selectedTimer = new QListWidgetItem;
        selectedTimer = ui->listWidget->currentItem();
        timersAndAlarmsList[index].Set_node("");
        selectedTimer->setText("Timer: " + QTime(0,0,0).addMSecs(timersAndAlarmsList[index].timeMillSec()).toString() + timersAndAlarmsList[index].node());
}

void MainWindow::on_listWidget_itemSelectionChanged()
{
    if (clickSound) { playerChange->play(); }
    ui->AddToGroupOfTimers->setEnabled(true);
    ui->RemoveFromGroupOfTimers->setEnabled(true);
    ui->start->setEnabled(true);
    ui->Delete->setEnabled(true);
    ui->StartGroup->setEnabled(true);
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    item = new QListWidgetItem;
    if(doubleclick) {
        on_start_clicked();
    }
}














void MainWindow::on_actionhours_minutes_seconds_triggered()
{
    ui->timeEdit->setDisplayFormat("hh:mm:ss");
}
void MainWindow::on_actionhours_minutes_triggered()
{
    ui->timeEdit->setDisplayFormat("hh:mm");
}
void MainWindow::on_actionminutes_seconds_triggered()
{
    ui->timeEdit->setDisplayFormat("mm:ss");
}


void MainWindow::on_actionClick_Sound_triggered(bool checked)
{
    if(checked) { clickSound = false; }
    else { clickSound = true; }
}


void MainWindow::on_actionDouble_click_to_Start_triggered(bool checked)
{
    if(checked) { doubleclick = true; }
    else { doubleclick = false; }
}


void MainWindow::on_actionGroup_1_triggered()
{
    group = " Group 1";
}
void MainWindow::on_actionGroup_2_triggered()
{
    group = " Group 2";
}
void MainWindow::on_actionGroup_3_triggered()
{
    group = " Group 3";
}


void MainWindow::on_actionSecret_Box_Fun_triggered()
{
    ui->DisturbBox->setTristate(true);
    playerSecretBox->play();
    QMessageBox::warning(this,"WARNING!", "SECRET BOX!!!", QMessageBox::Ok);
    playerSecretBox->stop();
    ui->DisturbBox->setTristate(false);
}
