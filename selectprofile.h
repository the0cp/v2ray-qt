#ifndef SELECTPROFILE_H
#define SELECTPROFILE_H

#include <QDialog>

namespace Ui {
class selectProfile;
}

class selectProfile : public QDialog
{
    Q_OBJECT

public:
    explicit selectProfile(QWidget *parent = nullptr);
    ~selectProfile();

private:
    Ui::selectProfile *ui;
};

#endif // SELECTPROFILE_H
