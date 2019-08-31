#ifndef PLAYBACKWORKER_H
#define PLAYBACKWORKER_H


#include <QObject>
#include <QAtomicInteger>

class Track;

class PlaybackWorker : public QObject
{
    Q_OBJECT
public:
    explicit PlaybackWorker(const Track& track, QObject *parent = nullptr);

signals:
    void playSound(int soundId);
    void trackFinished();

public slots:
    void play();
    void stop();

private:
    /**
     * @brief reference to the Track class on which PlaybackWorker is working.
     */
    const Track& mTrack;
    /**
     * @brief flag used to be able to stop the worker from another thread.
     */
    QAtomicInteger<bool> mIsPlaying;
};

#endif // PLAYBACKWORKER_H
