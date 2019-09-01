#ifndef ALBUM_H
#define ALBUM_H

#include <QString>
#include <QDebug>
#include <QDebugStateSaver>

#include "gallery-core_global.h"

class GALLERYCORESHARED_EXPORT Album
{

public:
    explicit Album(const QString& name = "");

    int id() const;
    void setId(int id);
    QString name() const;
    void setName(const QString& name);

private:
    int mId;
    QString mName;
};

QDebug operator<<(QDebug debug, const Album& album)
{
    QDebugStateSaver saver(debug);
    debug.nospace() << "("
                    << "id: " << album.id() << ", "
                    << "name: " << album.name()
                    << ")";
    return debug;
}

#endif // ALBUM_H
