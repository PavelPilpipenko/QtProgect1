#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QTime>
#include <QTimer>
#include <QCheckBox>
#include <QMessageBox>
#include <QColor>
#include "timeclass.h"
#include "playlist.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, timeclass, playlist
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool clickSound;
    bool doubleclick;
    bool hints;
    QString group;

private slots:

    void update_timer(const unsigned long long int &index);
    void update_alarm(const unsigned long long int &index);
    void start_alarm(const unsigned long long int &index);
    void offButtons();


//UI:
    void on_addTimerButton_clicked();

    void on_start_clicked();

    void on_Delete_clicked();

    void on_addAlarmButton_clicked();

    void on_DisturbBox_clicked(bool checked);

    void on_AddToGroupOfTimers_clicked();

    void on_StartGroup_clicked();

    void on_RemoveFromGroupOfTimers_clicked();

    void on_listWidget_itemSelectionChanged();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);





    void on_actionhours_minutes_seconds_triggered();
    void on_actionhours_minutes_triggered();
    void on_actionminutes_seconds_triggered();

    void on_actionClick_Sound_triggered(bool checked);

    void on_actionDisable_hints_triggered(bool checked);

    void on_actionDouble_click_to_Start_triggered(bool checked);

    void on_actionGroup_1_triggered();
    void on_actionGroup_2_triggered();
    void on_actionGroup_3_triggered();

    void on_actionSecret_Box_Fun_triggered();

    //Music:
    void on_actionbeep_beep_Standart_triggered();
    void on_actionVery_loud_music_triggered();
    void on_actionHappy_New_Year_shortened_edition_triggered();
    void on_actionHappy_New_Year_Standart_triggered();
    void on_actionMellen_Gi_Remix_triggered();
    void on_actionGood_sound_triggered();
    void on_actionProsipaysa_Moi_Hazain_Fun_triggered();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
