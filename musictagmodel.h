#ifndef MUSICTAGMODEL_H
#define MUSICTAGMODEL_H
#include <QAbstractItemModel>
#include <QDir>
#include "musictagitem.h"


class MusicTagModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit MusicTagModel(QObject* parent = nullptr);
    ~MusicTagModel();

    QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    void appendItem(const QModelIndex &parent, MusicTagItem * item);
//    void setDeviceRootPath(const QString &path);
//    int appendScannedDirRelativePath(const QString &path);
//    void setScannedDirRelativePath(const QStringList &path);

private slots:

private:
//    void setupModelData(const QStringList &lines, MusicTagItem *parent);
//    QString deviceRootPath;
    MusicTagItem *rootItem;
};

#endif // MUSICTAGMODEL_H
