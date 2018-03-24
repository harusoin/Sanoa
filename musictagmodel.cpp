#include "musictagmodel.h"

MusicTagModel::MusicTagModel(QObject* parent) : QAbstractItemModel(parent)
{
    deviceRootPath="";

    QList<QVariant> rootData;
    rootData << tr("Album") << tr("Number") << tr("Title") << tr("Artist") << tr("Time");
    rootItem = new MusicTagItem(rootData);
//    setupModelData(data.split(QString("\n")), rootItem);
}

MusicTagModel::~MusicTagModel()
{
    delete rootItem;
}

QVariant MusicTagModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    MusicTagItem *item = static_cast<MusicTagItem*>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags MusicTagModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}

QVariant MusicTagModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex MusicTagModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    MusicTagItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<MusicTagItem*>(parent.internalPointer());

    MusicTagItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex MusicTagModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

    MusicTagItem *childItem = static_cast<MusicTagItem*>(child.internalPointer());
    MusicTagItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int MusicTagModel::rowCount(const QModelIndex &parent) const
{
    MusicTagItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<MusicTagItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int MusicTagModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<MusicTagItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

void MusicTagModel::appendItem(const QModelIndex &parent, MusicTagItem *item)
{
    if (parent.isValid())
        return static_cast<MusicTagItem*>(parent.internalPointer())->appendChild(item);
    else
        return rootItem->appendChild(item);
}
/*
void MusicTagModel::setDeviceRootPath(const QString &path)
{
    deviceRootPath=path;
}

int MusicTagModel::appendScannedDirRelativePath(const QString &path)
{
    if(deviceRootPath=="")return -1;
    QDir *scannedDir = new QDir(QString("%1/%2").arg(deviceRootPath).arg(path));
    if(!scannedDir->exists())return -1;

}

void MusicTagModel::setScannedDirRelativePath(const QStringList &path)
{
    scannedDirRelativePath=path;
}
*/
