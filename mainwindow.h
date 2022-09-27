#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QMenu>
#include <QAction>
#include <QUuid>
#include <QMessageBox>
#include <QRegularExpressionValidator>
#include <QFileDialog>

#include <QDebug>

#include "selectprofile.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initTray();

    void closeEvent(QCloseEvent *event);

    void _exit();

    bool loadConf(QString source, QString target);

    QString ip, uuid, remarks, protocol;

    int port, listening;

    bool isudp;

private slots:
    void on_btn_add_clicked();

    void on_btnGen_clicked();

    void on_btnLoad_clicked();

    void showProfileWindow();

private:
    Ui::MainWindow *ui;

    selectProfile *selectWindow;

    QMenu *menu;

    QMenu *mode;

    QMenu *help;

    QAction *actShow;

    QAction *actSelect;

    QAction *actExit;

    QAction *global;

    QAction *disableProxy;

    QAction *about;

    QSystemTrayIcon *tray;
};
#endif // MAINWINDOW_H
