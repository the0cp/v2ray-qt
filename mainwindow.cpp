#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configure.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    configure server;
    server.read_conf();

    selectWindow = new selectProfile();
    initTray();

}

void MainWindow::initTray()
{
    tray = new QSystemTrayIcon(this);

    QIcon icon = QIcon(":/res/v2ray-qt5.png");
    tray -> setIcon(icon);
    tray -> setToolTip("v2ray");

    menu = new QMenu(this);

    actShow = new QAction("Open");
    connect(actShow, &QAction::triggered, [this]{this -> show();});

    actSelect = new QAction("Select Profile");
    connect(actSelect, &QAction::triggered, this, &MainWindow::showProfileWindow);

    mode = new QMenu("Mode");
    global = new QAction("Global");
    global -> setCheckable(true);
    global -> setChecked(true);

    disableProxy = new QAction("No Proxy");
    global -> setCheckable(true);

    mode -> addAction(global);
    mode -> addAction(disableProxy);

    help = new QMenu("Help");
    about = new QAction("About");
    help -> addAction(about);

    actExit = new QAction("Exit");
    connect(actExit, &QAction::triggered, [this]{_exit();});

    menu -> addAction(actShow);
    menu -> addAction(actSelect);
    menu -> addMenu(mode);
    menu -> addMenu(help);
    menu -> addAction(actExit);

    tray -> setContextMenu(menu);

    tray -> show();

    tray -> showMessage("v2ray",
                        "v2ray is running!",
                        QSystemTrayIcon::Information,
                        1000);
    ui -> line_ip -> setValidator(
                new QRegularExpressionValidator
                (
                    QRegularExpression("\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b"), ui -> line_ip
    ));
    ui -> line_port -> setValidator(
                new QRegularExpressionValidator
                (
                    QRegularExpression("^([0-9]|[1-9]\\d|[1-9]\\d{2}|[1-9]\\d{3}|[1-5]\\d{4}|6[0-4]\\d{3}|65[0-4]\\d{2}|655[0-2]\\d|6553[0-5])$"), ui -> line_port
    ));
    ui -> line_listening -> setValidator(
                new QRegularExpressionValidator
                (
                    QRegularExpression("^([0-9]|[1-9]\\d|[1-9]\\d{2}|[1-9]\\d{3}|[1-5]\\d{4}|6[0-4]\\d{3}|65[0-4]\\d{2}|655[0-2]\\d|6553[0-5])$"), ui -> line_listening
    ));
}

bool MainWindow::loadConf(QString source, QString target)
{
    target = target + QFileInfo(source).fileName();

    if(source == target)
    {
        return true;
    }

    if(!QFile::exists(source))
    {
        return false;
    }

    QDir *createFile = new QDir;
    bool exist = createFile -> exists(target);


    if(exist)
    {
        QUuid id = QUuid::createUuid();
        QString strId = id.toString();
        strId.remove("{").remove("}");

        target = target.left(target.lastIndexOf(".")) + "-copy-" + strId + ".json";
    }

    qDebug()<<source;
    qDebug()<<target;

    if(!QFile::copy(source, target))
    {
        return false;
    }
    return true;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    this -> hide();
    event -> ignore();
}

void MainWindow::_exit()
{
    exit(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_add_clicked()
{
    //write json
    qDebug()<<"add";
    ip = ui -> line_ip -> text();
    port = ui -> line_port -> text().toInt();
    uuid = ui -> line_uuid -> text();
    remarks = ui -> line_remarks -> text();
    listening = ui -> line_listening -> text().toInt();
    switch(ui -> comboProtocol -> currentIndex())
    {
    case 0:
    {
        protocol = "https";
        break;
    }
    case 1:
    {
        protocol = "socks";
        break;
    }
    }

    switch(ui -> comboUDP -> currentIndex())
    {
    case 0:
    {
        isudp = false;
        break;
    }
    case 1:
    {
        isudp = true;
        break;
    }
    }

    if(ip == "" || port == NULL || uuid == "")
    {
        qDebug()<<"error";
        QMessageBox msg;
        msg.setText("Please set config correctly");
        msg.exec();
    }
    else
    {
        if(remarks == "")
        {
            remarks = uuid;
        }
        configure server;
        server.write_conf(ip,port,uuid,remarks,listening, isudp, protocol);
        ui -> line_ip -> clear();
        ui -> line_port -> clear();
        ui -> line_remarks -> clear();
        ui -> line_uuid -> clear();
    }
}



void MainWindow::on_btnGen_clicked()
{
    QUuid id = QUuid::createUuid();
    QString strId = id.toString();
    strId.remove("{").remove("}");
    qDebug() << strId;
    ui -> line_uuid -> setText(strId);
}


void MainWindow::on_btnLoad_clicked()
{
    QFileDialog *fileDia = new QFileDialog(this);
    fileDia -> setWindowTitle(QStringLiteral("Open configure"));
    fileDia -> setDirectory(QDir::homePath());
    fileDia -> setNameFilter("v2ray config file(*.json)");
    fileDia -> setFileMode(QFileDialog::ExistingFiles);
    fileDia -> setViewMode(QFileDialog::Detail);
    QStringList files;
    if(fileDia -> exec())
    {
        files = fileDia -> selectedFiles();
    }
    qDebug()<<files;
    for(int i=0; i < files.length(); i++)
    {
        loadConf(files[i], QDir::homePath() + "/v2ray/");
    }

}

void MainWindow::showProfileWindow()
{
    // place code to load all the profiles in a scrollable area;
    // use radio buttons in a table widget;
    selectWindow -> show();
}
