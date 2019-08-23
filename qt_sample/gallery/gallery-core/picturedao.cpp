#include "picturedao.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>

#include "picture.h"

PictureDao::PictureDao(QSqlDatabase& database) :
    mDatabase(database)
{

}

void PictureDao::init() const {
    if (!mDatabase.tables().contains("pictures")) {
        QSqlQuery query(mDatabase);
        if (!query.exec(QString("CREATE TABLE pictures (id INTEGER PRIMARY KEY AUTOINCREMENT, album_id INTEGER, url TEXT)"))) {
            qDebug() << "Cannot create pictures table: " << query.lastError();
        }
    }
}

void PictureDao::addPictureInAlbum(int albumId, Picture& picture) const {
    QSqlQuery query(mDatabase);
    query.prepare("SELECT * FROM albums where id=:id");
    query.bindValue(":id", albumId);
    query.exec();
    if (query.next()) {
        QSqlQuery insert(mDatabase);
        insert.prepare("INSERT INTO pictures (album_id, url) values(:album_id, :url)");
        insert.bindValue(":album_id", albumId);
        insert.bindValue(":url", picture.fileUrl());
        if (!insert.exec()) {
            qDebug() << "addPictureInAlbum: cannot insert pictures table: " << query.lastError();
        }
        qDebug() << "addPicture: url=" << picture.fileUrl();
        picture.setId(insert.lastInsertId().toInt());
    } else {
        qDebug() << "Empty album";
    }
}

void PictureDao::removePicture(int id) const {
    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM pictures where id=:id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "removePicture: cannot delete picture:" << id << ", err=" << query.lastError();
    }
}

void PictureDao::removePicturesForAlbum(int albumId) const {
    QSqlQuery query(mDatabase);
    query.prepare("DELET FROM pictures where album_id=:album_id");
    query.bindValue(":album_id", albumId);
    if (!query.exec()) {
        qDebug() << "removePicturesForAlbum: cannot delete album_id:" << albumId << ",err=" << query.lastError();
    }
}

PictureListPtr PictureDao::picturesForAlbum(int albumId) const {
    QSqlQuery query(mDatabase);
    query.prepare("SELECT * from pictures where album_id=:album_id");
    query.bindValue(":album_id", albumId);
    query.exec();
    PictureListPtr list(new PictureList());
    while(query.next()) {
        PicturePtr picture(new Picture());
        picture->setId(query.value("id").toInt());
        picture->setAlbumId(query.value("album_id").toInt());
        picture->setFileUrl(query.value("url").toString());
        list->push_back(std::move(picture));
    }

    return list;
}
