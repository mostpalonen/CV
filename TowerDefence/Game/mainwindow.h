#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include "ui_mainwindow.h"
#include "dialogstart.h"
#include "player.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QObject>
#include <QMainWindow>
#include "managers/gameeventhandler.h"
#include "managers/gameobjectmanager.h"
#include "managers/resourcemanager.h"
#include "managers/soundengine.h"
#include "tiles/buildingspace.h"
#include "towers/towerbase.h"
#include <memory>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{ 
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    // member attributes
    QGraphicsScene * scene = nullptr;
    QGraphicsPixmapItem * cursor = nullptr;
    class TowerBase * building = nullptr;
    QList<QPointF> pointsToFollow;

    //void setWindowSize(int x, int y);
    void generateMap();
    void createRoad();
    void spawnEnemy();
    void adjustSceneSize(int x, int y);
    void centerAndResize();
    void openDialog();
    void setCursor(QString file);
    void operateTextBrowser(QString text);

public slots:
    void startGame();
    void gameOver(bool win);
    void giveUp();
    void winRound();
    void setPlayerName(QString name);
    void buildWainola();
    void buildMikontalo();
    void buildMatriisi();
    void buildTTorni();
    void buildDuo();
    void cancelBuilding();
    void setResources();
    void checkResources();
    void passCost(int money, int mead, int concrete, int credits);
    void roundStatus(bool set);

private:
    Player * player_ = nullptr;
    int sizeX_ = 800;
    int sizeY_ = 800;
    std::string name_;

    class gameEventHandler * geh_ = nullptr;
    class ObjectManager * gom_ = nullptr;
    class ResourceManager * rm_ = nullptr;
    Ui::MainWindow *ui = nullptr;


};

#endif // MAINWINDOW_H
