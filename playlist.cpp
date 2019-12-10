#include "playlist.h"

playlist::playlist()
{
    playerAlarm = new QMediaPlayer;
    playerTimer = new QMediaPlayer;
    playerChange = new QMediaPlayer;
    playerTimer->setMedia(QUrl("qrc:/sounds/recources/alarm-clock-beep.mp3"));
    playerAlarm->setMedia(QUrl("qrc:/sounds/recources/Happy-New-Year-alarm.mp3"));
    playerChange->setMedia(QUrl("qrc:/sounds/recources/change button.mp3"));
    playerAlarm->setVolume(50);
}
