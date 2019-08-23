#include "picturemodel.h"

#include "album.h"
#include "albummodel.h"
#include "databasemanager.h"

#include <QDebug>

PictureModel::PictureModel(const AlbumModel& albumModel, QObject* parent) :
    QAbstractListModel(parent),
    mDb(DatabaseManager::instance()),
    mAlbumId(-1),
    mPictures(new PictureList())
{
    connect(&albumModel, &AlbumModel::rowsRemoved, this, &PictureModel::deletePicturesForAlbum);
}

void PictureModel::setAlbumId(int albumId)
{
    beginResetModel();
    mAlbumId = albumId;
    loadPictures(mAlbumId);
    endResetModel();
}

void PictureModel::loadPictures(int albumId)
{
    if (albumId <= 0) {
        mPictures.reset(new PictureList());
        return;
    }
    mPictures = mDb.pictureDao.picturesForAlbum(albumId);
}

QModelIndex PictureModel::addPicture(const Picture& picture) {
    int rowIndex = rowCount();
    beginInsertRows(QModelIndex(), rowIndex, rowIndex);
    PicturePtr newPicture(new Picture(picture));
    mDb.pictureDao.addPictureInAlbum(mAlbumId, *newPicture);
    mPictures->push_back(move(newPicture));
    endInsertRows();
    return index(rowIndex, 0);
}

void PictureModel::addPictureFromUrl(const QString& url) {
    qDebug() << "addPictureFromUrl: " << url;
    addPicture(Picture(QUrl(url)));
}

int PictureModel::rowCount(const QModelIndex& parent) const {
    (void) parent;

    return mPictures->size();
}

QVariant PictureModel::data(const QModelIndex& index, int role) const {
    if (!isIndexValid(index)) {
        return QVariant();
    }
    const Picture& picture = *mPictures->at(index.row());
    switch (role) {
    case Qt::DisplayRole:
        return picture.fileUrl().fileName();
        break;

    case Roles::UrlRole:
        return picture.fileUrl();
        break;

    case Roles::FilePathRole:
        return picture.fileUrl().toLocalFile();
        break;

    default:
        return QVariant();
    }
}


QHash<int, QByteArray> PictureModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Roles::FilePathRole] = "filepath";
    return roles;
}

bool PictureModel::removeRows(int row, int count, const QModelIndex& parent) {
    if (row < 0 || row >= rowCount() || count < 0 || (row + count) > rowCount()) {
        return false;
    }
    beginRemoveRows(parent, row, row + count - 1);
    int countLeft = count;
    while (countLeft--) {
        const Picture& picture = *mPictures->at(row + countLeft);
        mDb.pictureDao.removePicture(picture.id());
    }
    mPictures->erase(mPictures->begin() + row,
    mPictures->begin() + row + count);
    endRemoveRows();
    return true;
}

void PictureModel::clearAlbum() {
    setAlbumId(-1);
}

void PictureModel::deletePicturesForAlbum() {
    mDb.pictureDao.removePicturesForAlbum(mAlbumId);
    clearAlbum();
}

bool PictureModel::isIndexValid(const QModelIndex& index) const {
    if (index.row() < 0
            || index.row() >= rowCount()
            || !index.isValid()) {
        return false;
    }
    return true;
}
