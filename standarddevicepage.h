#ifndef STANDARDDEVICEPAGE_H
#define STANDARDDEVICEPAGE_H
#include "devicepage.h"
#include "musictagmodel.h"


class StandardDevicePage : public DevicePage
{
    Q_OBJECT
public:
    explicit StandardDevicePage(QObject *parent = nullptr);
    int setDeviceInfo();
    int setDeviceInfo(QStorageInfo storageInfo);
    int setUI(QStackedWidget *stackedWidget,DeviceTreeWidget *listWidget);
private:
    QStorageInfo mountedStandardStorageInfo;
    void scanMusicDir(QFileInfoList fileList);
};

#endif // STANDARDDEVICEPAGE_H
