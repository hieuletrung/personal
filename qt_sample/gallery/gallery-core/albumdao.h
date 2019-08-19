#ifndef ALBUMDAO_H
#define ALBUMDAO_H

#include <QVector>
#include <memory>

class QSqlDatabase;
class Album;

typedef std::unique_ptr<Album>     AlbumPtr;
typedef std::vector<AlbumPtr>      AlbumList;
typedef std::unique_ptr<AlbumList> AlbumListPtr;

class AlbumDao
{
public:
    AlbumDao(QSqlDatabase& database);
    void init() const;
    void addAlbum(Album& album) const;
    void updateAlbum(const Album& album) const;
    void removeAlbum(int id) const;
    AlbumListPtr albums() const;

private:
    QSqlDatabase& mDatabase;
};

#endif // ALBUMDAO_H
