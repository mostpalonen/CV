#include "dialoginfo.h"
#include "ui_dialoginfo.h"

DialogInfo::DialogInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogInfo)
{
    // Dialog for displaying info about gameplay and towers to help
    // player win the game

    MAXPAGE = 8;
    page_ = 0;
    ui->setupUi(this);
    auto back = ui->pushButtonBack;
    auto next = ui->pushButtonNext;
    auto close = ui->pushButtonClose;
    QGraphicsScene* scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);

    connect(next, SIGNAL(pressed()), this, SLOT(upPage()));
    connect(back, SIGNAL(pressed()), this, SLOT(downPage()));
    connect(close, SIGNAL(pressed()), this, SLOT(close()));

    back->setEnabled(false);
    updatePage();
}

DialogInfo::~DialogInfo() {
    delete ui;
}

void DialogInfo::upPage() {
    page_ += 1;
    if (page_ == 0) {
        ui->pushButtonBack->setEnabled(false);
    } else {
        ui->pushButtonBack->setEnabled(true);

    }
    if (page_ == MAXPAGE) {
        ui->pushButtonNext->setEnabled(false);
    } else {
        ui->pushButtonNext->setEnabled(true);
    }
    updatePage();
}

void DialogInfo::downPage() {
    page_ -= 1;
    if (page_ == 0) {
        ui->pushButtonBack->setEnabled(false);
    } else {
        ui->pushButtonBack->setEnabled(true);
    }
    if (page_ == MAXPAGE) {
        ui->pushButtonNext->setEnabled(false);
    } else {
        ui->pushButtonNext->setEnabled(true);
    }
    updatePage();
}

void DialogInfo::updatePage() {
    if (page_ == 0) {
        ui->graphicsView->scene()->clear();
        ui->text->setText("Sinun on puolustettava TTY:tä Pirkanmaalle levinneitä uhkia vastaan. "
                          "Peli on tornipuolustuspeli. Resurssien salliessa voit rakentaa eri tyyppisiä "
                          "torneja, jotka hyökkäävät eteneviä uhkia vastaan jokainen omalla ammuksellaan. "
                          "Resurssit tässä pelissä ovat raha, betoni, sima ja opintopisteet. "
                          "Mikäli jokin vihollisista pääsee TTY:lle asti, ne hyökkäävät sen kimppuun. "
                          "Jos näitä vihollisia ei tuhota, on peli pian menetetty.");
    } else if (page_ == 1) {
        ui->graphicsView->scene()->clear();
        ui->text->setText("Pelimekaniikat: \n"
                          "Pelissä edetään aalloittain. Joka aallon aikana kohtaat uuden haasteen "
                          "vihollisjoukon muodossa. Pelialue on jaettu 10 x 10 ruudukkoon. Osa ruudukosta "
                          "on tien varaama, eikä kyseisille ruuduille voi rakentaa. Jos kykenet päihittämään "
                          "hyökkäävän aallon vihollisia, aalto päättyy voitokkaasti. Voit pitää hengähdystauon "
                          "ja jatkaa halutessasi seuraavalle aallolle. Resursseja saa joka aallon lopuksi, "
                          "nujertamalla vihollisia sekä "
                          "rakentamalla Duon/Duoja.");
    } else if (page_ == 2) {
        ui->graphicsView->scene()->clear();
        ui->text->setText("Käytössäsi olevat tornit: \n"
                          "1. Wäinölä \n"
                          "Perustorni, jonka hintana on 50 rahaa. Wäinölän asukkaat heittelevät "
                          "kaljatölkeillä Hervantaan tunkeutujia.");
        ui->graphicsView->scene()->addPixmap(QPixmap(":images/wainola.png"));

    } else if (page_ == 3) {
        ui->graphicsView->scene()->clear();
        ui->text->setText("2. Mikontalo \n"
                          "Enemmän vahinkoa tekevä, torakoita vihollisten päälle sylkevä "
                          "betonilinnoitus. Mikontalo kustantaa 150 rahaa, 50 betonia ja "
                          "50 simaa.");
        ui->graphicsView->scene()->addPixmap(QPixmap(":images/mikontalo.png"));
    } else if (page_ == 4) {
        ui->graphicsView->scene()->clear();
        ui->text->setText("3. Matriisintornit \n"
                          "Hervannan eliittiä! Näiltä näköaloilta kelpaa heitellä rahaa alas "
                          "vähäosaisempien joukkoon. Korkealta pudotettu raha vaikuttaa vihollisiin "
                          "erittäin ikävällä tavalla (heidän näkökulmastaan). Raha ottaa todella kipeää "
                          "sekä he alkavat haaveilla muuttavansa matriisintorneihin. "
                          "Torni kustantaa 300 rahaa, "
                          "500 betonia, 450 simaa ja 15 opintipistettä.");
        ui->graphicsView->scene()->addPixmap(QPixmap(":images/matriisi.png"));
    } else if (page_ == 5) {
        ui->graphicsView->scene()->clear();
        ui->text->setText("4. Tieteentornit \n"
                          "Monen rakastamat tieteentornit. Täällä asuu niin puolustushenkistä porukkaa, että "
                          "tornista lentää kahdenlaisia ammuksia yhden sijasta. Torni maksaa 200 rahaa, "
                          "150 betonia, 100 simaa sekä 4 opintopistettä");
        ui->graphicsView->scene()->addPixmap(QPixmap(":images/ttorni.png"));
    } else if (page_ == 6) {
        ui->graphicsView->scene()->clear();
        ui->text->setText("5. Duo, herkku \n"
                          "Jos hervanta olisi ihminen, jolla olisi kaksi sydäntä, niin Duo olisi niistä toinen. "
                          "Duo kustantaa 120 rahaa, 100 betonia, 75 simaa sekä 2 opintopistettä. "
                          "Duo tuottaa 21 sekunnin välein 60 rahaa, 30 betonia, 15 simaa sekä kaksi opintopistettä.");
        ui->graphicsView->scene()->addPixmap(QPixmap(":images/duo.png"));
    } else if (page_ == 7) {
        ui->graphicsView->scene()->clear();
        ui->text->setText("6. TTY \n"
                          "Toiminnan tukikohta. TTY luodaan kartan oikeaan alakulmaan automaattisesti. TTY:llä on "
                          "50 osumapistettä. Älä anna niiden loppua!");
        ui->graphicsView->scene()->addPixmap(QPixmap(":images/base.png"));
    } else if (page_ == 8) {
        ui->graphicsView->scene()->clear();
        ui->text->setText("Onnea peliin. Tarvitset sitä taistossa TUNIA vastaan. \n"
                          "Jos haluat testata peliä käytä nimeä 'testaaja'. ");
    }
}

void DialogInfo::close() {
    QWidget::close();
}
