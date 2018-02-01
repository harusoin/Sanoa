#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 表示モデルを用意
    QStandardItemModel * model = new QStandardItemModel();

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
}

void MainWindow::browse()
{
    QString directory =
        QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("Find Files"), QDir::currentPath()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
