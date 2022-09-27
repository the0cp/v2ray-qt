#ifndef CONFIGURE_H
#define CONFIGURE_H

#include <QString>
#include <QSettings>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonArray>
#include <QFile>

class configure
{
public:
    QString path;

    void write_conf(QString IP, int PORT, QString UUID, QString REMARKS, int LISTENING, bool isUDP, QString PROTOCOL);

    int read_conf();
};

#endif // CONFIGURE_H
