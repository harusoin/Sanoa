#include "mainwindow.h"
#include <QApplication>
#include <QLibraryInfo>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator qtTranslator;
    QString qmFilesPath = QString("%1/translations").arg(PROJECT_DIRECTORY);
    if(qtTranslator.load("Sanoa_" + QLocale::system().name(),qmFilesPath))a.installTranslator(&qtTranslator);
    QTranslator qtTranslator2;
    if(qtTranslator2.load("qt_" + QLocale::system().name(),QLibraryInfo::location(QLibraryInfo::TranslationsPath)))a.installTranslator(&qtTranslator2);

    MainWindow w;
    w.show();

    return a.exec();
}
