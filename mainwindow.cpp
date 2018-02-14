#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adddevice.h"
#include "mtpdevicepage.h"
#include "standarddevicepage.h"
#include "devicetreewidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->DeviceList->setColumnCount(1);
    DevicePage *page =new StandardDevicePage;
    page->setDeviceInfo();
    page->setUI(ui->stackedWidget,ui->DeviceList);
    devicePages.append(page);


    //以下テスト
    QStorageInfo storage = QStorageInfo::root();

    qDebug() << storage.rootPath();
    if (storage.isReadOnly())
        qDebug() << "isReadOnly:" << storage.isReadOnly();

    qDebug() << "name:" << storage.name();
    qDebug() << "device:" << storage.device();
    qDebug() << "fileSystemType:" << storage.fileSystemType();
    qDebug() << "size:" << storage.bytesTotal()/1000/1000 << "MB";
    qDebug() << "availableSize:" << storage.bytesAvailable()/1000/1000 << "MB";
    qDebug() << "--------------:";

    foreach (const QStorageInfo &storage, QStorageInfo::mountedVolumes()) {
        if (storage.isValid() && storage.isReady()) {
            if (!storage.isReadOnly()) {
                qDebug() << "name:" << storage.name();
                qDebug() << "device:" << storage.device();
                qDebug() << storage.rootPath();
                qDebug() << "fileSystemType:" << storage.fileSystemType();
                qDebug() << "size:" << storage.bytesTotal()/1000/1000 << "MB";
                qDebug() << "availableSize:" << storage.bytesAvailable()/1000/1000 << "MB";
                qDebug() << "blocksize:" << storage.blockSize();
                qDebug() << "displyname:" << storage.displayName();
            }
        }
    }
}

void MainWindow::browse()
{
    QString directory =
        QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("Find Files"), QDir::currentPath()));
}

void MainWindow::addDevice()
{
    AddDevice aDevice;
    DevicePage *page;

    if (aDevice.exec()) {
        switch (aDevice.selectedDeviceType) {
        case DEVICETYPE_NULL:
            break;
        case DEVICETYPE_STANDARD:
            page=new StandardDevicePage;
            page->setDeviceInfo(aDevice.selectedStandardStorage);
            page->setUI(ui->stackedWidget,ui->DeviceList);
            devicePages.append(page);
            break;
        case DEVICETYPE_MTP:
            page=new MtpDevicePage;
            page->setDeviceInfo(aDevice.selectedMtpStorage);
            page->setUI(ui->stackedWidget,ui->DeviceList);
            devicePages.append(page);
            break;
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
