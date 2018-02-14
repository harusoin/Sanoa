#include "devicetreewidget.h"

DeviceTreeWidget::DeviceTreeWidget(QWidget *parent) : QTreeWidget(parent)
{
}

void DeviceTreeWidget::currentItemChangedToID(QTreeWidgetItem *item)
{
    int id = item->data(0,Qt::UserRole).toInt() ;
    emit currentIDChanged(id) ;
}
