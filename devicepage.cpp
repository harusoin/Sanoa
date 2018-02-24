#include "devicepage.h"

DevicePage::DevicePage(QObject *parent) : QObject(parent)
{
    mountedDeviceType=DEVICETYPE_NULL;
}

void DevicePage::setScannedDirPathes(QStringList pathes)
{
    scannedDirRelativePath=pathes;
}
