#include "selectprofile.h"
#include "ui_selectprofile.h"

selectProfile::selectProfile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selectProfile)
{
    ui->setupUi(this);
}

selectProfile::~selectProfile()
{
    delete ui;
}
