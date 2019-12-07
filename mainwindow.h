#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QTime>
#include <QTimer>
#include "timeclass.h"
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, timeclass
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void update_timer(QListWidgetItem *selTimer);
    void on_addTimerBurron_clicked();

    void on_start_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
