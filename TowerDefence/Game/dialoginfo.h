#ifndef DIALOGINFO_H
#define DIALOGINFO_H

#include <QDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QPixmap>
#include "towers/wainola.h"

namespace Ui {
class DialogInfo;
}

class DialogInfo : public QDialog
{
    Q_OBJECT

public:
    explicit DialogInfo(QWidget *parent = nullptr);
    ~DialogInfo();

public slots:
    void upPage();
    void downPage();
    void updatePage();
    void close();

private:
    Ui::DialogInfo *ui;
    int page_;
    int MAXPAGE;
};

#endif // DIALOGINFO_H
