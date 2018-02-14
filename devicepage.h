#ifndef DEVICEPAGE_H
#define DEVICEPAGE_H

#include <QObject>
#include <QStorageInfo>
#include <QVector>
#include "defines.h"
#include "devicetreewidget.h"

QT_BEGIN_NAMESPACE
class QStackedWidget;
class QTreeWidget;
QT_END_NAMESPACE

class DevicePage : public QObject
{
    Q_OBJECT
public:
    explicit DevicePage(QObject *parent = nullptr);
    virtual int setDeviceInfo() = 0;
    virtual int setDeviceInfo(MTP_STORAGE_ID_t storageInfo) = 0;
    virtual int setDeviceInfo(QStorageInfo storageInfo) = 0;
    virtual int setUI(QStackedWidget *stackedWidget,DeviceTreeWidget *listWidget) = 0;

signals:

public slots:
protected:
    DeviceType mountedDeviceType;
    QString mountedDeviceName;
    QVector<QString> mountedStorageName;
};

#endif // DEVICEPAGE_H
