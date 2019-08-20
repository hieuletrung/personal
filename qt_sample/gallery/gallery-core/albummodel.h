#ifndef ALBUMMODEL_H
#define ALBUMMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <vector>
#include <memory>

#include "gallery-core_global.h"
#include "album.h"
#include "databasemanager.h"

class GALLERYCORESHARED_EXPORT AlbumModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        NameRole,
    };

    AlbumModel(QObject* parent = nullptr);

    QModelIndex addAlbum(const Album& album);

    /**
     * @brief Get the list size
     * @param parent
     * @return
     */
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    /**
     * @brief Get a specific piece of information about the data to display
     * @param index
     * @param role
     * @return
     */
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    /**
     * @brief Used to update data
     * @param index
     * @param value
     * @param role
     * @return
     */
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    /**
     * @brief Remove data
     * @param row
     * @param count
     * @param parent
     * @return
     */
    bool removeRows(int row, int count, const QModelIndex& parent) override;

    /**
     * @brief indicate to the framework the name for each "role". We will explain in a few paragraphs what a role is
     * @param index
     * @param value
     * @param role
     * @return
     */
    QHash<int, QByteArray> roleNames() const override;

private:
    bool isIndexValid(const QModelIndex& index) const;

private:
    DatabaseManager& mDb;
    AlbumListPtr mAlbums;
};

#endif // ALBUMMODEL_H
