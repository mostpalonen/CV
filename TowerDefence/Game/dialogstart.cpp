#include "dialogstart.h"
#include "ui_dialogstart.h"

DialogStart::DialogStart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogStart)
{
    // Dialog to get info about player

    ui->setupUi(this);
    ui->line->setAlignment(Qt::AlignRight);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Aloita peli");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("EIKU");
    ui->pushButtonInfo->setText("INFO");
    ui->infoLabel->setText("Jos haluat testata käytä nimeä 'testaaja', \n"
                           "jolloin saat 10000 kaikkia resursseja.");
    connect(ui->pushButtonInfo, SIGNAL(pressed()), this, SLOT(openInfo()));
}

void DialogStart::on_buttonBox_accepted() {
    DialogStart::accept();
}

void DialogStart::on_buttonBox_rejected(){
    DialogStart::reject();
}

void DialogStart::openInfo() {
    DialogInfo dialog;
    dialog.setModal(true);
    if (dialog.exec() == QDialog::Rejected) {
    }
}


DialogStart::~DialogStart() {
    delete ui;
}

void DialogStart::on_pushButton_clicked() {
    if (ui->line->text() != "") {
        emit passName(ui->line->text());
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    } else {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}
