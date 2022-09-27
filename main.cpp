#include "mainwindow.h"

#include <QApplication>
#include <QSettings>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(!QFileInfo("config.ini").exists())
    {
        QSettings *setting = new QSettings("config.ini", QSettings::IniFormat);
        setting -> setValue("/server/path", "");
        delete setting;
    }
    if(!QDir(QDir::homePath() + "/v2ray/").exists())
    {
        QDir dir;
        dir.mkpath(QDir::homePath() + "/v2ray/");
    }

    MainWindow w;
    return a.exec();
}
