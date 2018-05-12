#include "standarddevicepage.h"
#include <QStackedWidget>
#include <QTableWidget>
#include <QGraphicsView>
#include <QGridLayout>
#include <QLabel>
#include <QDebug>

#include "taglib/fileref.h"
#include "taglib/tag.h"
#include "taglib/tpropertymap.h"

StandardDevicePage::StandardDevicePage(QObject *parent) : DevicePage(parent)
{
    scannedDirRelativePath << "Music";
}

void StandardDevicePage::scanMusicDir(QDir scannedDir)
{
    qDebug() << scannedDir.absolutePath();
    QStringList fsi = scannedDir.entryList();
    qDebug() << fsi.size();
    QFileInfoList fileList = scannedDir.entryInfoList();
    TagLib::FileRef *musicFileTemp;
    QListIterator<QFileInfo> iterator_list(fileList);
    while (iterator_list.hasNext())
    {
        QFileInfo fi = iterator_list.next();
        if ( !(fi.fileName() == "..") && !(fi.fileName() == ".") )
        {
            if (fi.isFile())
            {
                musicFileTemp = new TagLib::FileRef(scannedDir.absoluteFilePath(fi.fileName()).toLocal8Bit());
                if(!musicFileTemp->isNull() && musicFileTemp->tag()) {

                  TagLib::Tag *tag = musicFileTemp->tag();

                  qDebug() << "-- TAG (basic) --";
                  qDebug() << "title   - \"" << QString::fromStdString(tag->title().to8Bit())   << "\"";
                  qDebug() << "artist  - \"" << QString::fromStdString(tag->artist().to8Bit())  << "\"";
                  qDebug() << "album   - \"" << QString::fromStdString(tag->album().to8Bit())   << "\"";
                  qDebug() << "year    - \"" << tag->year()    << "\"";
                  qDebug() << "comment - \"" << QString::fromStdString(tag->comment().to8Bit()) << "\"";
                  qDebug() << "track   - \"" << tag->track()   << "\"";
                  qDebug() << "genre   - \"" << QString::fromStdString(tag->genre().to8Bit())   << "\"";

                  TagLib::PropertyMap tags = musicFileTemp->file()->properties();

                  unsigned int longest = 0;
                  for(TagLib::PropertyMap::ConstIterator i = tags.begin(); i != tags.end(); ++i) {
                    if (i->first.size() > longest) {
                      longest = i->first.size();
                    }
                  }

                }
            }
            else if (fi.isDir())
            {
                if(scannedDir.cd(fi.fileName())){
                    scanMusicDir(scannedDir);
                    scannedDir.cdUp();
                }
            }
        }
    }
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

    QDir scannedDir(mountedStandardStorageInfo.rootPath());
//    scannedDir.setFilter(QDir::NoSymLinks);
    for(int i = 0;i < scannedDirRelativePath.size();++i)
    {
        if(scannedDir.cd(scannedDirRelativePath.at(i))){
            scanMusicDir(scannedDir);
            scannedDir.cdUp();
        }
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
