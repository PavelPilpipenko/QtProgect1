#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QMediaPlayer>
#include <QUrl>

class playlist
{

public:
    QMediaPlayer *playerTimer;
    QMediaPlayer *playerAlarm;
    QMediaPlayer *playerChange;
    QMediaPlayer *playerSecretBox;


    playlist();
};

#endif // PLAYLIST_H
