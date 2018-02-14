#ifndef DEVICETREEWIDGET_H
#define DEVICETREEWIDGET_H
#include <QTreeWidget>

class DeviceTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    DeviceTreeWidget(QWidget *parent = Q_NULLPTR);
public slots:
    void currentItemChangedToID(QTreeWidgetItem *item);
signals:
    void currentIDChanged(int id);
};

#endif // DEVICETREEWIDGET_H
