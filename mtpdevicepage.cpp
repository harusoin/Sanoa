#include "mtpdevicepage.h"
#include <QStackedWidget>
#include <QTableWidget>
#include <QGraphicsView>
#include <QGridLayout>
#include <QLabel>

MtpDevicePage::MtpDevicePage(QObject *parent) : DevicePage(parent)
{
    rawdevices=NULL;
    mtpDevice=NULL;
}

int MtpDevicePage::setDeviceInfo(MTP_STORAGE_ID_t storageInfo)
{
    if(mountedDeviceType!=DEVICETYPE_NULL)return -1;
    int numrawdevices;
    LIBMTP_error_number_t err;
    int i;

    err = LIBMTP_Detect_Raw_Devices(&rawdevices, &numrawdevices);
    switch (err) {
    case LIBMTP_ERROR_NO_DEVICE_ATTACHED:
        return LIBMTP_ERROR_NO_DEVICE_ATTACHED;
        break;
    case LIBMTP_ERROR_CONNECTING:
        return LIBMTP_ERROR_CONNECTING;
    case LIBMTP_ERROR_MEMORY_ALLOCATION:
        return LIBMTP_ERROR_MEMORY_ALLOCATION;
    case LIBMTP_ERROR_NONE:
        break;
    case LIBMTP_ERROR_GENERAL:
    default:
      return 1;
    }
    for (i = 0; i < numrawdevices; i++) {
        if(rawdevices[i].bus_location==storageInfo.busno && rawdevices[i].devnum==storageInfo.devno)
        {
            mtpDevice = LIBMTP_Open_Raw_Device_Uncached(&rawdevices[i]);
            if (mtpDevice == NULL) {
              continue;
            }
            LIBMTP_Clear_Errorstack(mtpDevice);
            QString modelName = QString(LIBMTP_Get_Modelname(mtpDevice));
            if(0!=LIBMTP_Get_Storage(mtpDevice,LIBMTP_STORAGE_SORTBY_NOTSORTED))
            {
                LIBMTP_Clear_Errorstack(mtpDevice);
                continue;
            }
            mountedDeviceName=modelName;
            LIBMTP_devicestorage_t *storage;
            for (storage = mtpDevice->storage; storage != 0; storage = storage->next) {
                mountedMtpStorageInfo.append(storage);
                mountedStorageName.append(QString(storage->StorageDescription));
                mountedDeviceType=DEVICETYPE_MTP;
            }
            if(mountedDeviceType==DEVICETYPE_MTP)return 0;
            LIBMTP_Release_Device(mtpDevice);
            mtpDevice=NULL;
        }
    }
    free(rawdevices);
    rawdevices=NULL;
    return -1;
}

int MtpDevicePage::setUI(QStackedWidget *stackedWidget, DeviceTreeWidget *listWidget)
{
    if(mountedDeviceType==DEVICETYPE_NULL)return -1;

    QTreeWidgetItem *itemDevice;
    QTreeWidgetItem *itemStorage;
    QTabWidget *tabWidget;
    QTableWidget *musictable;
    QVBoxLayout *vlayout;
    QGridLayout *layout;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QWidget *widget;
    QLabel *name;

    QStringList devicename;
    devicename << mountedDeviceName;

    itemDevice = new QTreeWidgetItem(devicename);
    listWidget->addTopLevelItem(itemDevice);

    for (int i=0; i < mountedMtpStorageInfo.size(); ++i){
        tabWidget=new QTabWidget;

        vlayout=new QVBoxLayout;
        name=new QLabel;
        name->setText(QString("%1/%2").arg(mountedDeviceName).arg(mountedStorageName[i]));
        vlayout->addWidget(name);
        widget=new QWidget;
        widget->setLayout(vlayout);
        tabWidget->addTab(widget, tr("Infomation"));

        musictable=new QTableWidget;
        musictable->setColumnCount(5);
        musictable->setHorizontalHeaderLabels( QStringList() << tr("Album") << tr("Number") << tr("Title") << tr("Artist") << tr("Time"));
        scene=new QGraphicsScene;
        view=new QGraphicsView;
        view->setScene(scene);
        widget=new QWidget;
        layout = new QGridLayout;
        layout->addWidget(musictable);
        widget->setLayout(layout);
        tabWidget->addTab(widget, tr("Music"));
        widget=new QWidget;
        layout = new QGridLayout;
        layout->addWidget(view);
        widget->setLayout(layout);
        tabWidget->addTab(widget, tr("Album"));
        widget=new QWidget;
        layout = new QGridLayout;
        layout->addWidget(tabWidget);
        widget->setLayout(layout);
        stackedWidget->addWidget(widget);

        QStringList storageName;
        storageName << mountedStorageName[i];

        itemStorage = new QTreeWidgetItem(storageName);
        itemStorage->setData(0,Qt::UserRole, stackedWidget->indexOf(widget));
        itemDevice->addChild(itemStorage);
    }


    return 0;
}

MtpDevicePage::~MtpDevicePage()
{
    if(mtpDevice!=NULL)LIBMTP_Release_Device(mtpDevice);
    if(rawdevices!=NULL)free(rawdevices);
}
