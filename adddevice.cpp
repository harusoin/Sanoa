#include "adddevice.h"

#include <QtWidgets>

AddDevice::AddDevice(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout *layout;

    nameLabel = new QLabel(tr("DeviceList"));
    okButton = new QPushButton(tr("OK"));
    cancelButton = new QPushButton(tr("Cancel"));

    deviceTable=new QTableWidget;
    deviceTable->setColumnCount(3);
    deviceTable->setRowCount(10);
    deviceTable->setHorizontalHeaderLabels( QStringList() << tr("Name") << tr("Available") << tr("Total"));
    deviceTable->setColumnWidth(0,180);
    deviceTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    deviceTable->setSelectionMode( QAbstractItemView::ContiguousSelection );
    deviceTable->setSelectionBehavior( QAbstractItemView::SelectRows );
    deviceTable->horizontalHeader()->setStretchLastSection(true);
    deviceTable->setMinimumSize(400,200);

    QStorageInfo storage = QStorageInfo::root();

    QByteArray rootdevice = storage.device();

    int row = 0;
    QString availablesize;
    QString totalsize;
    foreach (const QStorageInfo &storage, QStorageInfo::mountedVolumes()) {
        if (rootdevice!=storage.device() && storage.isValid() && storage.isReady()) {
            availablesize = QString("%1MB").arg(storage.bytesAvailable()/1000/1000);
            totalsize = QString("%1MB").arg(storage.bytesTotal()/1000/1000);
            deviceTable->setItem( row, 0, new QTableWidgetItem(storage.name()));
            deviceTable->setItem( row, 1, new QTableWidgetItem(availablesize));
            deviceTable->setItem( row, 2, new QTableWidgetItem(totalsize));
            deviceTable->setRowHeight( row, 20 );
            deviceTypeMap[row]=DEVICETYPE_STANDARD;
            standardStorageMap[row]=storage;
            row++;
        }
    }

    int numrawdevices;
    LIBMTP_error_number_t err;
    int i;

    err = LIBMTP_Detect_Raw_Devices(&rawdevices, &numrawdevices);
    if(err==LIBMTP_ERROR_NONE) {
        for (i = 0; i < numrawdevices; i++) {
            LIBMTP_mtpdevice_t *mtpDevice;
            mtpDevice = LIBMTP_Open_Raw_Device_Uncached(&rawdevices[i]);
            if (mtpDevice == NULL) {
              qDebug() << "Unable to open raw device " << i;
              continue;
            }
            LIBMTP_Clear_Errorstack(mtpDevice);
            QString modelName = QString("%1").arg(LIBMTP_Get_Modelname(mtpDevice));
            if(0!=LIBMTP_Get_Storage(mtpDevice,LIBMTP_STORAGE_SORTBY_NOTSORTED))
            {
                qDebug() << "LIBMTP_Get_Storage()";
                LIBMTP_Clear_Errorstack(mtpDevice);
                continue;
            }
            deviceTable->setItem( row, 0, new QTableWidgetItem(modelName));
            deviceTable->setRowHeight( row, 20 );
            deviceTypeMap[row]=DEVICETYPE_MTP;
            mtpStorageMap[row].busno=rawdevices[i].bus_location;
            mtpStorageMap[row].devno=rawdevices[i].devnum;
            row++;
            LIBMTP_Release_Device(mtpDevice);
        }
    }


    deviceTable->setRowCount(row);
    selectedDeviceType=DEVICETYPE_NULL;


    layout = new QVBoxLayout;
    layout->addWidget(nameLabel);
    layout->addWidget(deviceTable);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    layout->addLayout(buttonLayout);

    setLayout(layout);

    connect(deviceTable, &QTableWidget::itemSelectionChanged, this, &AddDevice::setDeviceInfo);
    connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

    setWindowTitle(tr("Add a Device"));
}
void AddDevice::resizeEvent(QResizeEvent *event) {

    QDialog::resizeEvent(event);
}
void AddDevice::setDeviceInfo(){
    int currentrow=deviceTable->currentRow();
    selectedDeviceType=deviceTypeMap[currentrow];
    switch (selectedDeviceType) {
    case DEVICETYPE_STANDARD:
        selectedStandardStorage=standardStorageMap[currentrow];
        break;
    case DEVICETYPE_MTP:
        selectedMtpStorage=mtpStorageMap[currentrow];
        break;
    case DEVICETYPE_NULL:
        break;
    }

}
AddDevice::~AddDevice()
{
    free(rawdevices);
}
