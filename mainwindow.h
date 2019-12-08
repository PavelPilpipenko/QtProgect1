#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QTime>
#include <QTimer>
#include <QCheckBox>
#include <QMediaPlayer>
#include <QUrl>
#include <QMessageBox>
#include "timeclass.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, timeclass
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QMediaPlayer *playerTimer;
    QMediaPlayer *playerAlarm;
private slots:

    void update_timer(const unsigned long long int &index);
    void update_alarm(const unsigned long long int &index);
    void on_addTimerButton_clicked();

    void on_start_clicked();

    void on_Delete_clicked();

    void on_addAlarmButton_clicked();

    void on_DisturbBox_clicked(bool checked);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
