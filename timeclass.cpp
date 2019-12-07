#include "timeclass.h"

Timer::Timer() {
    timer = new QTimer;
    timer->setInterval(1000);
}

int Timer::timeMillSec()
{
    return _timeMillSec;
}

QTimer *Timer::ttimer()
{
    return timer;
}

void Timer::Set_timeMillSec(const int &time)
{
    Timer::_timeMillSec = time;
}

timeclass::timeclass()
{
}
