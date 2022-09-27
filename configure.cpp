#include "configure.h"
#include "mainwindow.h"

#include <QStandardPaths>
#include <QDir>
#include <QMessageBox>

void configure::write_conf(QString IP, int PORT, QString UUID, QString REMARKS, int LISTENING, bool isUDP, QString PROTOCOL)
{
    QJsonObject inboundjson;
    inboundjson.insert("port", LISTENING);
    inboundjson.insert("listen", "127.0.0.1");
    inboundjson.insert("protocol", PROTOCOL);
    QJsonObject inboundSettings;
    inboundSettings.insert("udp", isUDP);

    inboundjson.insert("settings", inboundSettings);

    QJsonArray inboundArray;
    inboundArray.append(inboundjson);   //in

    QJsonObject outboundjson;
    outboundjson.insert("protocol", "vmess");

    QJsonObject outboundSettings;

    QJsonObject vnext;

    QJsonArray vnextArray;

    QJsonObject users;
    QJsonArray usersArray;
    users.insert("id", UUID);
    usersArray.append(users);


    vnext.insert("address", IP);
    vnext.insert("port", PORT);
    vnext.insert("users", usersArray);

    vnextArray.append(vnext);
    outboundSettings.insert("vnext", vnextArray);

    outboundjson.insert("settings", outboundSettings);

    QJsonObject outbound;
    outbound.insert("protocol", "freedom");
    outbound.insert("tag", "direct");
    outbound.insert("settings", {});


    QJsonArray outboundArray;
    outboundArray.append(outboundjson);
    outboundArray.append(outbound); //out

    QJsonObject routingRule;
    routingRule.insert("tyoe", "field");
    QJsonArray geoip;
    geoip.append("geoip:private");
    routingRule.insert("ip", geoip);
    routingRule.insert("outboundTag", "direct");
    QJsonArray routingRuleArray;
    routingRuleArray.append(routingRule);

    QJsonObject routing;
    routing.insert("domainStrategy", "IPOnDemand");
    routing.insert("rules", routingRuleArray);

    QJsonObject root;
    root.insert("inbounds", inboundArray);
    root.insert("outbounds", outboundArray);
    root.insert("routing", routing);

    QJsonDocument doc;
    doc.setObject(root);

    if(QFileInfo(QDir::homePath() + "/v2ray/" + REMARKS + ".json").exists())
    {
        QMessageBox msg;
        msg.setText("Already existed. Please use another remarks!!!");
        msg.exec();
        return;
    }

    QFile file(QDir::homePath() + "/v2ray/" + REMARKS + ".json");
    if(!file.open(QIODevice::Append|QIODevice::Text))
    {
        QMessageBox msg;
        msg.setText("Error: Cannot write configure");
        msg.exec();
        return;
    }

    QTextStream stream(&file);
    stream << doc.toJson();
    file.close();
}

int configure::read_conf()
{
    QSettings *setting = new QSettings("config.ini", QSettings::IniFormat);
    path = setting -> value("/server/path").toString();
    delete setting;

    //qDebug()<<path;


    return 0;
}
