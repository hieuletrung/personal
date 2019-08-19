#include "picturedao.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

#include "picture.h"

PictureDao::PictureDao(QSqlDatabase& database) :
    mDatabase(database)
{

}

void PictureDao::init() const {
    if (!mDatabase.tables().contains("pictures")) {
        QSqlQuery query(mDatabase);
        query.exec(QString("CREATE TABLE pictures id INTEGER PRIMARY KEY AUTOINCREMENT, album_id INTEGER, url TEXT"));
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
        insert.exec();
        picture.setId(insert.lastInsertId().toInt());
    }
}

void PictureDao::removePicture(int id) const {
    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM pictures where id=:id");
    query.bindValue(":id", id);
    query.exec();
}

void PictureDao::removePicturesForAlbum(int albumId) const {
    QSqlQuery query(mDatabase);
    query.prepare("DELET FROM pictures where album_id=:album_id");
    query.bindValue(":album_id", albumId);
    query.exec();
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
