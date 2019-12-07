#include "timeclass.h"

int timeclass::timeMillSec()
{
    return _timeMillSec;
}

void timeclass::Set_timeMillSec(const int &time)
{
    _timeMillSec = time;
}

timeclass::timeclass()
{
    timer = new QTimer;
    timer->setInterval(1000);
}
