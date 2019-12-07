#ifndef TIMECLASS_H
#define TIMECLASS_H

#include <vector>
#include <QTimer>

enum type {not_setted, isTimer, isAlarm};
struct TimerAndAlarm {
private:
    QTimer *_clock;
    int _timeMillSec;
    type _type;
public:
    int timeMillSec();
    type type();
    QTimer *clock();

    void Set_timeMillSec(const int &time);
    void Set_type(const int &numOftype);

    TimerAndAlarm();
};



class timeclass : public TimerAndAlarm
{
public:
    std::vector<TimerAndAlarm> timersAndAlarmsList;
    timeclass();
};

#endif // TIMECLASS_H
