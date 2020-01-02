#ifndef DIALOGSTART_H
#define DIALOGSTART_H

#include <QDialog>
//#include "ui_dialogstart.h"
#include "dialoginfo.h"

namespace Ui {
class DialogStart;
}

class DialogStart : public QDialog
{
    Q_OBJECT

public:
    explicit DialogStart(QWidget *parent = nullptr);
    ~DialogStart();

public slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void openInfo();

signals:
    void passName(QString data);

private slots:
    void on_pushButton_clicked();

private:
    Ui::DialogStart *ui;
    bool nameSet_ = false;
};

#endif // DIALOGSTART_H
