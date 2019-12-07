#include "timeclass.h"

TimerAndAlarm::TimerAndAlarm() {
    _clock = new QTimer;
    _clock->setInterval(1000);
    _type = not_setted;
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

void TimerAndAlarm::Set_timeMillSec(const int &time)
{
    TimerAndAlarm::_timeMillSec = time;
}

timeclass::timeclass()
{
}
