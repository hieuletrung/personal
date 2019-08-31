#ifndef SOUNDEVENT_H
#define SOUNDEVENT_H

#include <QtGlobal>
#include <QMetaType>

#include "Serializable.h"

class SoundEvent : public Serializable
{
public:
    SoundEvent(qint64 timestamp = 0, int soundId = 0);
    ~SoundEvent();

    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

    /**
     * @brief current time of the SoundEvent in milliseconds since the beginning of the track.
     */
    qint64 timestamp;
    /**
     * @brief The ID of the sound that has been played.
     */
    int soundId;
};

// Registers SoundEvent to the QMetaType register, making it available for QVariant.
Q_DECLARE_METATYPE(SoundEvent)

#endif // SOUNDEVENT_H
