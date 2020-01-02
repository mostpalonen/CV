#include "soundengine.h"

SoundEngine::SoundEngine()
{
    loop_ = new QMediaPlaylist(this);
    loop_->setPlaybackMode(QMediaPlaylist::Loop);
}

void SoundEngine::playSound(QString sound) {
    // Plays the called media

    QMediaPlayer * m = new QMediaPlayer(this);
    if (sound == "death") {
        m->setMedia(QUrl("qrc:/sounds/death.mp3"));
        m->setVolume(13);
    } else if (sound == "bossmusic") {
        loop_->clear();
        loop_->addMedia(QUrl("qrc:/sounds/bossmusic.mp3"));
        m->setVolume(55);
        m->setPlaylist(loop_);
    } else if (sound == "music") {
        loop_->clear();
        loop_->addMedia(QUrl("qrc:/sounds/music.mp3"));
        m->setPlaylist(loop_);
    } else if (sound == "start") {
        m->setMedia(QUrl("qrc:/sounds/start.mp3"));
    } else if (sound == "lose") {
        m->setMedia(QUrl("qrc:/sounds/lose.mp3"));
    } else if (sound == "win") {
        m->setMedia(QUrl("qrc:/sounds/wavewin.mp3"));
    } else if (sound == "finalbossmusic") {
        loop_->clear();
        loop_->addMedia(QUrl("qrc:/sounds/finalbossmusic.mp3"));
        m->setPlaylist(loop_);
        m->setVolume(45);
    } else if (sound == "alert") {
        m->setMedia(QUrl("qrc:/sounds/alert.mp3"));
        m->setVolume(65);
    }
    media_.push_back(m);
    m->play();
}

void SoundEngine::stopSounds() {

    for (QMediaPlayer * p : media_) {
        p->stop();
        media_.pop_front();
        delete p;
    }
    loop_->clear();
}
