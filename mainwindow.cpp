#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adddevice.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // モデルの設定
    ui->DeviceList->setModel(model);
    // 追加アイテムのテキストリスト
    QString ItemText = tr("Library");

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
    item = new QStandardItem;
    Q_CHECK_PTR(item);
    item->setText( ItemText );
    item->setEditable( false );
    model->appendRow( item ); // リストビューはアイテムを列に追加

    tabWidget=new QTabWidget;
    musictable=new QTableWidget;
    musictable->setColumnCount(5);
    musictable->setHorizontalHeaderLabels( QStringList() << tr("Album") << tr("Number") << tr("Title") << tr("Artist") << tr("Time"));
    scene=new QGraphicsScene;
    view=new QGraphicsView(scene);
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
    ui->page->setLayout(layout);


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

    if (aDevice.exec()) {
        QString name = aDevice.nameText->text();

        emit sendDeviceInfo(name);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
