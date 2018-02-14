#ifndef MTPDEVICEPAGE_H
#define MTPDEVICEPAGE_H
#include "devicepage.h"
#include "libmtp.h"


class MtpDevicePage : public DevicePage
{
    Q_OBJECT
public:
    explicit MtpDevicePage(QObject *parent = nullptr);
    ~MtpDevicePage();
    int setDeviceInfo(MTP_STORAGE_ID_t storageInfo);
    int setUI(QStackedWidget *stackedWidget,DeviceTreeWidget *listWidget);
private:
    QVector<LIBMTP_devicestorage_t*> mountedMtpStorageInfo;
    LIBMTP_raw_device_t *rawdevices;
    LIBMTP_mtpdevice_t *mtpDevice;
};

#endif // MTPDEVICEPAGE_H
