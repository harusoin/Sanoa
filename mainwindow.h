#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <QTextEdit>
#include <QGraphicsView>
#include <QTableWidget>
#include <QGridLayout>
#include <QtWidgets>
#include <QVector>
#include "devicepage.h"

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

private:
    // 表示モデルを用意

    Ui::MainWindow *ui;
    QVector<DevicePage*>devicePages;
};

#endif // MAINWINDOW_H
