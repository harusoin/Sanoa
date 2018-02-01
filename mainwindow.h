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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
