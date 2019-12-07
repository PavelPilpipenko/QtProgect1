#ifndef TIMECLASS_H
#define TIMECLASS_H

#include <vector>
#include <QTimer>

struct Timer {
private:
    QTimer *timer;
    int _timeMillSec;
public:
    int timeMillSec();
    QTimer *ttimer();
    void Set_timeMillSec(const int &time);

    Timer();
};



class timeclass : public Timer
{
public:
    std::vector<Timer> timersList;
    timeclass();
};

#endif // TIMECLASS_H
