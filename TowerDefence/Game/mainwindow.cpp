#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QPen>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QPushButton>
#include <QDebug>
#include <QList>
#include <QRectF>
#include <QDesktopWidget>
#include <QStyle>
#include <iostream>

#include "towers/headquarter.h"
#include "bullets/bullet.h"
#include "enemies/enemybase.h"
#include "towers/towerbase.h"
#include <managers/gameeventhandler.h>
#include "managers/gameobjectmanager.h"
#include "managers/resourcemanager.h"
#include "player.h"
#include <string>

SoundEngine * sndEngine;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                            ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->startButton->setEnabled(true);
    ui->cancelBuild->setDisabled(true);
    setFixedSize(1200, 720);

    // Connect all the push buttons
    connect(ui->startButton, SIGNAL(pressed()), this , SLOT(startGame()));
    connect(ui->buildWainola, SIGNAL(pressed()), this, SLOT(buildWainola()));
    connect(ui->buildMikontalo, SIGNAL(pressed()), this, SLOT(buildMikontalo()));
    connect(ui->buildMatriisi, SIGNAL(pressed()), this, SLOT(buildMatriisi()));
    connect(ui->buildTTorni, SIGNAL(pressed()), this, SLOT(buildTTorni()));
    connect(ui->buildDuo, SIGNAL(pressed()), this, SLOT(buildDuo()));
    connect(ui->giveUpButton, SIGNAL(pressed()), this, SLOT(giveUp()));
    connect(ui->cancelBuild, SIGNAL(pressed()), this, SLOT(cancelBuilding()));

    player_ = new Player("", {});
    openDialog();

    QString n = QString::fromStdString(player_->getName());
    setWindowTitle("Pirkanmaan valloitus : " + n);
    operateTextBrowser("Tervetuloa pelaamaan, " + n + "!");

    //Luodaan uusi scene ja gameEventHandler
    scene = new QGraphicsScene(0, 0, 32, 32, this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Creates gameEventHandler, gameObjectManager, resourceManager and soundEngine
    geh_ = new gameEventHandler(this, scene);
    gom_ = new ObjectManager(this, scene);
    rm_ = new ResourceManager(this, gom_);
    sndEngine = new SoundEngine();

    // Start general timers
    QTimer * resTimer = new QTimer(this);
    connect(resTimer, SIGNAL(timeout()), this, SLOT(setResources()));
    resTimer->start(50);

    QTimer * checkResTimer = new QTimer(this);
    connect(checkResTimer, SIGNAL(timeout()), this, SLOT(checkResources()));
    checkResTimer->start(50);

    cursor = nullptr;
    building = nullptr;
    setMouseTracking(true);
    setResources();
    generateMap();

    // Test mode resources
    if (player_->getName() == "testaaja") {
        rm_->forceResource("money", 10000);
        rm_->forceResource("concrete", 10000);
        rm_->forceResource("mead", 10000);
        rm_->forceResource("credits", 10000);
    }
}

MainWindow::~MainWindow(){}

void MainWindow::generateMap() {
    // Calls gom and geh to generate the map and sets HQ in correct position

    for (int i = 0; i <= 9; ++i) {
        for (int j = 0; j <= 9; ++j) {
            gom_->addSpace(i*88, j*88);
        }
    }
    gom_->resetSpaceStates();
    geh_->createRoad();

    //Asetetaan HQ
    gom_->setBuildMode(2);
    gom_->addTower(QPointF(792, 792));
    gom_->setBuildMode(0);
}

void MainWindow::openDialog() {
    // Opens the starting dialog

    DialogStart dialog;
    dialog.setModal(true);
    connect(&dialog, SIGNAL(passName(QString)), this, SLOT(setPlayerName(QString)));

    if (dialog.exec() == QDialog::Rejected) {
        exit(EXIT_SUCCESS);
    }
}

void MainWindow::setCursor(QString file) {
    // To set modified cursor

    // if there is a cursor, remove it first
    if (cursor) {
        scene->removeItem(cursor);
        delete cursor;
    }
    QPixmap pixmap = QPixmap(file);
    QGuiApplication::setOverrideCursor(QCursor(pixmap));
}

void MainWindow::operateTextBrowser(QString text) {
    // Sets given text to UI's textBrowser
    ui->textBrowser->setText(text);
}

void MainWindow::setResources() {
    // Sets info about resources to UI
    ui->labelMoney->setText("Raha: " + QString::number(rm_->getResource("money")));
    ui->labelMead->setText("Sima: " + QString::number(rm_->getResource("mead")));
    ui->labelConcrete->setText("Betoni: " + QString::number(rm_->getResource("concrete")));
    ui->labelCredits->setText("Opintopisteet: " + QString::number(rm_->getResource("credits")));
}

void MainWindow::checkResources() {
    // Checks if player has enough recources to build a certain building.
    // If not sets the build button disabled.

    ui->labelHealth->setText("TTY:n osumapisteet: " + QString::number(gom_->getHqHealth()));
    if (gom_->getHqHealth() <= 0) {
        gameOver(false);
    }
    // Wäinölä
    if (rm_->checkResources(1)) {
        ui->buildWainola->setEnabled(true);
    } else {
        ui->buildWainola->setDisabled(true);
    }

    // Mikontalo
    if (rm_->checkResources(3)) {
        ui->buildMikontalo->setEnabled(true);
    } else {
        ui->buildMikontalo->setDisabled(true);
    }

    // Matriisit
    if (rm_->checkResources(4)) {
        ui->buildMatriisi->setEnabled(true);
    } else {
        ui->buildMatriisi->setDisabled(true);
    }

    // TTorni
    if (rm_->checkResources(5)) {
        ui->buildTTorni->setEnabled(true);
    } else {
        ui->buildTTorni->setDisabled(true);
    }

    // Duo
    if (rm_->checkResources(6) &&
            gom_->checkDuos()) {
        ui->buildDuo->setEnabled(true);
    } else {
        ui->buildDuo->setDisabled(true);
    }
    if(!gom_->checkDuos()) {
        ui->buildDuo->setText("Max määrä rakennettu");
    }
}

void MainWindow::passCost(int money, int concrete, int mead, int credits) {
    // Pass the cost of given building to resourceManager
    rm_->modifyResource("money", money);
    rm_->modifyResource("concrete", concrete);
    rm_->modifyResource("mead", mead);
    rm_->modifyResource("credits", credits);
}

void MainWindow::roundStatus(bool set) {
    gom_->roundStatus(set);
}

void MainWindow::startGame() {
    ui->startButton->setEnabled(false);
    operateTextBrowser("Peli alkaa...");
    ui->buildDuo->setText("Rakenna Duo");
    geh_->startWave();
}

void MainWindow::gameOver(bool win) {
    // Calls gom, geh and rm to reset their states to new game
    // and resets UI
    if (win == false) {
        gom_->setHqHp(0);
        geh_->gameOver(false);
        gom_->gameOver();

        operateTextBrowser("TTY tuhoutui...");

    } else {
       geh_->gameOver(true);
       gom_->gameOver();
    }

    ui->startButton->setEnabled(true);

    if (player_->getName() == "testaaja") {
        rm_->forceResource("money", 10000);
        rm_->forceResource("concrete", 10000);
        rm_->forceResource("mead", 10000);
        rm_->forceResource("credits", 10000);
    } else {
        rm_->forceResource("money", 175);
        rm_->forceResource("concrete", 30);
        rm_->forceResource("mead", 25);
        rm_->forceResource("credits", 0);
    }
    ui->buildDuo->setText("Rakenna Duo");
    gom_->setHqHp(50);
}

void MainWindow::giveUp() {
    gameOver(false);
}

void MainWindow::winRound() {
    ui->startButton->setEnabled(true);
}

void MainWindow::setPlayerName(QString name) {
    player_->setName(name.toStdString());
}

// These are the methods for building a certain tower.
// When called they call the gameObjectManager to build
// tower and set a custom cursor.
void MainWindow::buildWainola() {
    if (rm_->checkResources(1)) {
        gom_->setBuildMode(1);
        ui->cancelBuild->setEnabled(true);
        setCursor(":images/wainola.png");
    }
}

void MainWindow::buildMikontalo() {
    if (rm_->checkResources(3)) {
        gom_->setBuildMode(3);
        setCursor(":images/mikontalo.png");
        ui->cancelBuild->setEnabled(true);
    }
}

void MainWindow::buildMatriisi() {
    if (rm_->checkResources(4)){
        gom_->setBuildMode(4);
        setCursor(":images/matriisi.png");
        ui->cancelBuild->setEnabled(true);
    }
}

void MainWindow::buildTTorni() {
    if (rm_->checkResources(5)){
        gom_->setBuildMode(5);
        setCursor(":images/ttorni.png");
        ui->cancelBuild->setEnabled(true);
    }
}
void MainWindow::buildDuo() {
    if (rm_->checkResources(6)){
        gom_->setBuildMode(6);
        setCursor(":images/duo.png");
        ui->cancelBuild->setEnabled(true);
    }
}

void MainWindow::cancelBuilding() {
    QGuiApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
    ui->cancelBuild->setDisabled(true);
}
