#ifndef SOUNDENGINE_H
#define SOUNDENGINE_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class SoundEngine : public QObject
{ Q_OBJECT
public:
    SoundEngine();
    void playSound(QString sound);
    void stopSounds();

private:
    QList <QMediaPlayer *> media_;
    QMediaPlaylist * loop_;
};

#endif // SOUNDENGINE_H
