#ifndef SANOA_ADDDEVICE_H
#define SANOA_ADDDEVICE_H

#include <QDialog>
#include "libmtp.h"
#include <QStorageInfo>
#include <QMap>
#include "defines.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QTextEdit;
class QLineEdit;
class QTableWidget;
QT_END_NAMESPACE

class AddDevice : public QDialog
{
    Q_OBJECT

private slots:
    void setDeviceInfo();

public:
    AddDevice(QWidget *parent = 0);
    ~AddDevice();
    DeviceType selectedDeviceType;
    QStorageInfo selectedStandardStorage;
    MTP_STORAGE_ID_t selectedMtpStorage;

private:
    void resizeEvent(QResizeEvent *event);
    QPushButton *okButton;
    QPushButton *cancelButton;
    QLabel *nameLabel;
    QTableWidget *deviceTable;
    LIBMTP_raw_device_t *rawdevices;
    QMap<int, DeviceType> deviceTypeMap;
    QMap<int, QStorageInfo> standardStorageMap;
    QMap<int, MTP_STORAGE_ID_t> mtpStorageMap;
};

#endif // SANOA_ADDDEVICE_H
