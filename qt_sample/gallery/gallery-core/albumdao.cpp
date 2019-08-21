#include "albumdao.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QVariant>
#include <QSqlError>
#include <QDebug>

#include "databasemanager.h"
#include "album.h"

AlbumDao::AlbumDao(QSqlDatabase& database) :
    mDatabase(database)
{

}

void AlbumDao::init() const {
    if (!mDatabase.tables().contains("albums")) {
        QSqlQuery query(mDatabase);
        if (!query.exec("CREATE TABLE albums(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)")) {
            qDebug() << "Cannot create albums table: " << query.lastError();
        }
    }
}

void AlbumDao::addAlbum(Album &album) const {
    QSqlQuery query(mDatabase);
    query.prepare("INSERT INTO albums (name) VALUES (:name)");
    query.bindValue(":name", album.name());
    if (!query.exec()) {
        qDebug() << "addAlbum: cannot add: " << query.lastError();
    }
    album.setId(query.lastInsertId().toInt());
}

void AlbumDao::updateAlbum(const Album &album) const {
    QSqlQuery query(mDatabase);
    query.prepare("UPDATE albums set name=:name when id=:id");
    query.bindValue(":name", album.name());
    query.bindValue(":id", album.id());
    if (!query.exec()) {
        qDebug() << "updateAlbum: cannot update: " << query.lastError();
    }
}

void AlbumDao::removeAlbum(int id) const {
    QSqlQuery query(mDatabase);
    query.prepare("DELETE albums where id=:id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "removeAlbum: cannot remove: " << id << ",err=" << query.lastError();
    }
}

AlbumListPtr AlbumDao::albums() const {
    QSqlQuery query("SELECT * from albums", mDatabase);
    query.exec();
    AlbumListPtr list(new AlbumList);
    while(query.next()) {
        AlbumPtr album(new Album());
        album->setId(query.value("id").toInt());
        album->setName(query.value("name").toString());
        list->push_back(std::move(album));
    }

    return list;
}
