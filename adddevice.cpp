#include "adddevice.h"

#include <QtWidgets>

AddDevice::AddDevice(QWidget *parent) : QDialog(parent)
{
    QTabWidget *tabWidget;
    QTableWidget *deviceTable;
    QVBoxLayout *layout;

    nameLabel = new QLabel(tr("DeviceList"));
    okButton = new QPushButton(tr("OK"));
    cancelButton = new QPushButton(tr("Cancel"));

    tabWidget=new QTabWidget;
    deviceTable=new QTableWidget;
    deviceTable->setColumnCount(3);
    deviceTable->setRowCount(10);
    deviceTable->setHorizontalHeaderLabels( QStringList() << tr("Name") << tr("Available") << tr("Total"));
    deviceTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    deviceTable->setSelectionMode( QAbstractItemView::ContiguousSelection );
    deviceTable->setSelectionBehavior( QAbstractItemView::SelectRows );

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
            row++;
        }
    }
    deviceTable->setRowCount(row);
    deviceTable->setCurrentItem(deviceTable->item( 0, 0 ));


    layout = new QVBoxLayout;
    layout->addWidget(nameLabel);
    layout->addWidget(deviceTable);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    layout->addLayout(buttonLayout);

    setLayout(layout);

    connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

    setWindowTitle(tr("Add a Device"));
}
