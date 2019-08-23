#ifndef PICTUREMODEL_H
#define PICTUREMODEL_H

#include <memory>
#include <vector>

#include <QAbstractListModel>

#include "gallery-core_global.h"
#include "picture.h"
#include "databasemanager.h"

class Album;
class AlbumModel;

class GALLERYCORESHARED_EXPORT PictureModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        UrlRole = Qt::UserRole + 1,
        FilePathRole
    };

    PictureModel(const AlbumModel& albumModel, QObject* parent = nullptr);

    QModelIndex addPicture(const Picture& picture);
    Q_INVOKABLE void addPictureFromUrl(const QString& url);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    bool removeRows(int row, int count, const QModelIndex& parent) override;

    Q_INVOKABLE void setAlbumId(int albumId);
    void clearAlbum();
    QHash<int, QByteArray> roleNames() const override;

public slots:
    void deletePicturesForAlbum();

private:
    void loadPictures(int albumId);
    bool isIndexValid(const QModelIndex& index) const;

private:
    DatabaseManager& mDb;
    int mAlbumId;
    PictureListPtr mPictures;
};

#endif // PICTUREMODEL_H
