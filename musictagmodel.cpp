#include "musictagmodel.h"

MusicTagModel::MusicTagModel(QObject* parent) : QAbstractItemModel(parent)
{
    deviceRootPath="";
}

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
