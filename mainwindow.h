#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QTime>
#include <QTimer>
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

private slots:

    void update_timer(const unsigned long long int &index);
    void on_addTimerBurron_clicked();

    void on_start_clicked();

    void on_Delete_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
