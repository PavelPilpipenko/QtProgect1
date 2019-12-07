#ifndef TIMECLASS_H
#define TIMECLASS_H

#include <vector>
#include <QTimer>

class timeclass
{
private:
    int _timeMillSec;
public:
    QTimer *timer;
    std::vector<int> timersListTime;
    int timeMillSec();
    void Set_timeMillSec(const int &time);
    timeclass();
};

#endif // TIMECLASS_H
