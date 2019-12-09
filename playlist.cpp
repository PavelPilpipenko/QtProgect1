#include "playlist.h"

playlist::playlist()
{
    playerAlarm = new QMediaPlayer;
    playerTimer = new QMediaPlayer;
    playerChange = new QMediaPlayer;
    playerSecretBox = new QMediaPlayer;
    playerTimer->setMedia(QUrl("qrc:/sounds/recources/alarm-clock-beep.mp3"));
    playerAlarm->setMedia(QUrl("qrc:/sounds/recources/alarm-sound.mp3"));
    playerSecretBox->setMedia(QUrl("qrc:/sounds/recources/Secret-Box-Sound.mp3"));
    playerChange->setMedia(QUrl("qrc:/sounds/recources/change button.mp3"));
    playerSecretBox->setVolume(50);
    playerAlarm->setVolume(50);
}
