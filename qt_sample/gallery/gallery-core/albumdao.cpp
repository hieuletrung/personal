#include "albumdao.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QVariant>

#include "databasemanager.h"
#include "album.h"

AlbumDao::AlbumDao(QSqlDatabase& database) :
    mDatabase(database)
{

}

void AlbumDao::init() const {
    if (!mDatabase.tables().contains("albums")) {
        QSqlQuery query(mDatabase);
        query.exec("CREATE TABLE albums (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT");
    }
}

void AlbumDao::addAlbum(Album &album) const {
    QSqlQuery query(mDatabase);
    query.prepare("INSERT INTO albums (name) VALUES (:name)");
    query.bindValue(":name", album.name());
    query.exec();
    album.setId(query.lastInsertId().toInt());
}

void AlbumDao::updateAlbum(const Album &album) const {
    QSqlQuery query(mDatabase);
    query.prepare("UPDATE albums set name=:name when id=:id");
    query.bindValue(":name", album.name());
    query.bindValue(":id", album.id());
    query.exec();
}

void AlbumDao::removeAlbum(int id) const {
    QSqlQuery query(mDatabase);
    query.prepare("DELETE albums where id=:id");
    query.bindValue(":id", id);
    query.exec();
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
