#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QTextEdit>
#include <QGraphicsView>
#include <QTableView>
#include <QTableWidget>
#include <QGridLayout>
#include <QtWidgets>
#include <QUsb>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void browse();
    void addDevice();

signals:
    void sendDeviceInfo(QString name);

private:
    // 表示モデルを用意
    QStandardItemModel * model = new QStandardItemModel();

    Ui::MainWindow *ui;
    QUsbManager *mUsbManager = new QUsbManager;
};

#endif // MAINWINDOW_H
