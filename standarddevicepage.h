#ifndef STANDARDDEVICEPAGE_H
#define STANDARDDEVICEPAGE_H
#include "devicepage.h"


class StandardDevicePage : public DevicePage
{
    Q_OBJECT
public:
    explicit StandardDevicePage(QObject *parent = nullptr);
    int setDeviceInfo();
    int setDeviceInfo(QStorageInfo storageInfo);
    int setDeviceInfo(MTP_STORAGE_ID_t storageInfo);
    int setUI(QStackedWidget *stackedWidget,DeviceTreeWidget *listWidget);
private:
    QStorageInfo mountedStandardStorageInfo;
};

#endif // STANDARDDEVICEPAGE_H
