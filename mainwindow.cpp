#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // モデルの設定
    ui->DeviceList->setModel(model);
    // 追加アイテムのテキストリスト
    QStringList listItemText;
    listItemText << "ライブラリ";

    // 設定モデルの取得
    model = qobject_cast<QStandardItemModel*>(ui->DeviceList->model());
    // テキストアイテムの追加
    QStandardItem * item = NULL;
    QTabWidget *tabWidget;
    QTableWidget *musictable;
    QGridLayout *layout;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QWidget *widget;
    foreach ( QString text, listItemText )
    {
        item = new QStandardItem;
        Q_CHECK_PTR(item);
        item->setText( text );
        item->setEditable( false );
        model->appendRow( item ); // リストビューはアイテムを列に追加

        tabWidget=new QTabWidget;
        musictable=new QTableWidget;
        musictable->setColumnCount(5);
        musictable->setHorizontalHeaderLabels( QStringList() << tr("アルバム") << tr("番号") << tr("タイトル") << tr("アーティスト") << tr("長さ"));
        scene=new QGraphicsScene;
        view=new QGraphicsView(scene);
        widget=new QWidget;
        layout = new QGridLayout;
        layout->addWidget(musictable);
        widget->setLayout(layout);
        tabWidget->addTab(widget, tr("曲"));
        widget=new QWidget;
        layout = new QGridLayout;
        layout->addWidget(view);
        widget->setLayout(layout);
        tabWidget->addTab(widget, tr("アルバム"));
        widget=new QWidget;
        layout = new QGridLayout;
        layout->addWidget(tabWidget);
        ui->page->setLayout(layout);
    }

    QObject::connect(mUsbManager, SIGNAL(deviceInserted(QtUsb::FilterList)),
                     this, SLOT(onDevInserted(QtUsb::FilterList)));
    QObject::connect(mUsbManager, SIGNAL(deviceRemoved(QtUsb::FilterList)), this,
                     SLOT(onDevRemoved(QtUsb::FilterList)));
}

void MainWindow::browse()
{
    QString directory =
        QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("Find Files"), QDir::currentPath()));
}

void MainWindow::onDevInserted(QtUsb::FilterList list) {
    QStandardItem * item = NULL;
    QString text;
    for (int i = 0; i < list.length(); i++) {
        QtUsb::DeviceFilter f = list.at(i);
        text.sprintf("V%04x:P%04x", f.vid, f.pid);
        item = new QStandardItem;
        Q_CHECK_PTR(item);
        item->setText( text );
        item->setEditable( false );
        model->appendRow( item ); // リストビューはアイテムを列に追加
    }
}

void MainWindow::onDevRemoved(QtUsb::FilterList list) {
    QString text;
    for (int i = 0; i < list.length(); i++) {
        QtUsb::DeviceFilter f = list.at(i);
        text.sprintf("V%04x:P%04x", f.vid, f.pid);
        QList<QStandardItem *> items = model->findItems(text);
        for(QStandardItem *x : items){
            model->removeRow(x->row());
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
