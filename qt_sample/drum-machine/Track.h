#ifndef TRACK_H
#define TRACK_H

#include <QObject>
#include <QVector>
#include <QElapsedTimer>
#include <memory>

#include "SoundEvent.h"
#include "Serializable.h"

class Track : public QObject, public Serializable
{
    Q_OBJECT
public:
    enum class State {
        STOPPED,
        PLAYING,
        RECORDING,
    };

    explicit Track(QObject *parent = nullptr);
    ~Track();

    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

    qint64 duration() const;
    State state() const;
    State previousState() const;
    quint64 elapsedTime() const;
    const std::vector<std::unique_ptr<SoundEvent>>& soundEvents() const;

signals:
    void stateChanged(State state);

public slots:
    void play();
    void record();
    void stop();
    void addSoundEvent(int soundEventId);

private:
    void clear();
    void setState(State state);

private:
    /**
     * @brief holds the duration of the Track class. This member is reset to 0 when a recording is started and updated when the recording is stopped.
     */
    qint64 mDuration;
    /**
     * @brief list of SoundEvents for the given Track. As the unique_ptr semantic states it, Track is the owner of the sound events.
     */
    std::vector<std::unique_ptr<SoundEvent>> mSoundEvents;
    /**
     * @brief started each time Track is played or recorded.
     */
    QElapsedTimer mTimer;
    /**
     * @brief the current State of Track class, which can have three possible values: STOPPED, PLAYING, RECORDING.
     */
    State mState;
    /**
     * @brief previous State of Track.
     * This is useful when you want to know which action to do on a new STOPPEDState.
     * We will have to stop the playback if mPreviousState is in the PLAYING state.
     */
    State mPreviousState;
};

#endif // TRACK_H
