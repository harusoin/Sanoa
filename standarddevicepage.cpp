#include "standarddevicepage.h"
#include <QStackedWidget>
#include <QTableWidget>
#include <QGraphicsView>
#include <QGridLayout>
#include <QLabel>

StandardDevicePage::StandardDevicePage(QObject *parent) : DevicePage(parent)
{

}

void StandardDevicePage::scanMusicDir(QFileInfoList fileList)
{

}

int StandardDevicePage::setDeviceInfo()
{
    if(mountedDeviceType!=DEVICETYPE_NULL)return -1;
    mountedDeviceName=tr("Library");
    mountedStorageName.append(tr("Storage"));
    mountedDeviceType=DEVICETYPE_STANDARD;
    mountedStandardStorageInfo=QStorageInfo::root();
    return 0;
}

int StandardDevicePage::setDeviceInfo(QStorageInfo storageInfo)
{
    if(mountedDeviceType!=DEVICETYPE_NULL)return -1;
    mountedDeviceName=storageInfo.name();
    mountedStorageName.append(tr("Storage"));
    mountedDeviceType=DEVICETYPE_STANDARD;
    mountedStandardStorageInfo=storageInfo;
    return 0;
}

int StandardDevicePage::setUI(QStackedWidget *stackedWidget, DeviceTreeWidget *listWidget)
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

    tabWidget=new QTabWidget;

    vlayout=new QVBoxLayout;
    name=new QLabel;
    name->setText(mountedDeviceName);
    vlayout->addWidget(name);
    widget=new QWidget;
    widget->setLayout(vlayout);
    tabWidget->addTab(widget, tr("Infomation"));

    musictable=new QTableWidget;
    musictable->setColumnCount(5);
    musictable->setHorizontalHeaderLabels( QStringList() << tr("Album") << tr("Number") << tr("Title") << tr("Artist") << tr("Time"));

    for(int i = 0;i < scannedDirPath.size();++i)
    {
        /*
        QDir scannedDir(QString("%1/%3").arg(mountedStandardStorageInfo.rootPath()).arg(scannedDirPath.at(i)));
        scannedDir.setFilter(QDir::Hidden | QDir::NoSymLinks);
        scanMusicDir(scannedDir.entryInfoList());
        */
        MusicTagModel *scannedDir = new MusicTagModel;
        scannedDir->setRootPath(mountedStandardStorageInfo.rootPath());
        scannedDir->setFilter(QDir::Filter);
    }


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
    storageName << mountedStorageName[0];

    itemStorage = new QTreeWidgetItem(storageName);
    itemStorage->setData(0,Qt::UserRole, stackedWidget->indexOf(widget));
    itemDevice->addChild(itemStorage);

    return 0;
}
