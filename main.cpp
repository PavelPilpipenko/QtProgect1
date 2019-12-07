/*
#include "QLabel"
Стандартная библиотека для тектовых рядков, изменения размеров окна и тд.
#include <QMessegeBox>
Библиотека вывода диалоговых окон.
#include <QPixMap>
Библиотека для работы с картинаками(Добавление картинок в UI).
*/


#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
