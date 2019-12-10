#include "timeclass.h"

TimerAndAlarm::TimerAndAlarm() {
    _clock = new QTimer;
    _clock->setInterval(1000);
    _type = not_setted;
    _node = "";
}

type TimerAndAlarm::type() {
    return _type;
}

int TimerAndAlarm::timeMillSec()
{
    return _timeMillSec;
}

QTimer *TimerAndAlarm::clock()
{
    return _clock;
}

QString TimerAndAlarm::node()
{
    return _node;
}

void TimerAndAlarm::Set_type(const int &numOftype) {
    if(numOftype == 0) {
        _type = not_setted;
    } else if(numOftype == 1) {
        _type = isTimer;
    } else if(numOftype == 2) {
        _type = isAlarm;
    } else {
        return;
    }
}

void TimerAndAlarm::Set_node(const QString &node)
{
    _node = node;
}

void TimerAndAlarm::Set_timeMillSec(const int &time)
{
    _timeMillSec = time;
}

timeclass::timeclass()
{
    currTimer = new QTimer;
    currTimer->setInterval(1000);
}
