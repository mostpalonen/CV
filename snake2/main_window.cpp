/*
####################################################################
# TIE-02201 Ohjelmointi 2: Perusteet, K2019                        #
# TIE-02207 Programming 2: Basics, S2019                           #
#                                                                  #
# Project4: Snake: The Revengeance                                 #
# Program description: "While revenge is served cold and vengeance #
#                       is served hot revengeance is often seen    #
#                       served with Cajun with a side of onion     #
#                       rings and often dumplings in the Orient."  #
#                       - urbandictionary                          #
#                                                                  #
# File: main_window.cpp                                            #
# Description: Defines a class implementing a UI for the game.     #
#                                                                  #
# Author: Joonas Palonen, 272784, joonas.palonen@tuni.fi           #
####################################################################
*/

#include "main_window.hh"
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QKeyEvent>
#include <QWidget>
#include <string>
#include <random>
#include <QDebug>

MainWindow::MainWindow(QWidget* parent):
    QMainWindow(parent) {

    ui_.setupUi(this);
    ui_.graphicsView->setScene(&scene_);

    connect(&timer_, &QTimer::timeout, this, &MainWindow::moveSnake);
    connect(&secTimer_, &QTimer::timeout, this, &MainWindow::updateClock);
}

// Handles the key inputs
void MainWindow::keyPressEvent(QKeyEvent* event) {
    if ( !paused_ )
    {
        // Moving the snake UP
        if ( event->key() == Qt::Key_W && lastDirection_ != 2 )
        {
            if ( !inverted_ )       // Normal controls
            {
                xDir_ = 0;
                yDir_ = -1;
                lastDirection_ = 1;
            }
            else                    // Inverted controls
            {
                xDir_ = 0;
                yDir_ = 1;
                lastDirection_ = 1;
            }
        }
        // Moving the snake DOWN
        if ( event->key() == Qt::Key_S && lastDirection_ != 1 )
        {
            if ( !inverted_ )       // Normal controls
            {
                xDir_ = 0;
                yDir_ = 1;
                lastDirection_ = 2;
            }
            else                    // Inverted controls
            {
                xDir_ = 0;
                yDir_ = -1;
                lastDirection_ = 2;
            }
        }
        // Moving the snake RIGHT
        if ( event->key() == Qt::Key_D && lastDirection_ != 4 )
        {
            if ( !inverted_ )       // Normal controls
            {
                xDir_ = 1;
                yDir_ = 0;
                lastDirection_ = 3;
            }
            else                    // Inverted controls
            {
                xDir_ = -1;
                yDir_ = 0;
                lastDirection_ = 3;
            }

        }
        // Moving the snake LEFT
        if ( event->key() == Qt::Key_A && lastDirection_ != 3 )
        {
            if ( !inverted_ )       // Normal controls
            {
                xDir_ = -1;
                yDir_ = 0;
                lastDirection_ = 4;
            }
            else                    // Inverted controls
            {
                xDir_ = 1;
                yDir_ = 0;
                lastDirection_ = 4;
            }
        }
    }
    // Reseting the game using R key. Checks that the game is running before excecuting
    if ( event->key() == Qt::Key_R && !reseted_ )
    {
        reseted_ = true;
        MainWindow::on_resetButton_clicked();
    }
    // Pausing the game using P key. Checks that the game is running before excecuting
    if ( event->key() == Qt::Key_P && !reseted_ )
    {
        MainWindow::on_pauseButton_clicked();
    }
    // Closing the MainWindow using ESC kay
    if ( event->key() == Qt::Key_Escape )
    {
        MainWindow::close();
    }
}

// Starts the game
void MainWindow::on_playButton_clicked() {
    // Sets the ui components' status correclty
    reseted_ = false;
    ui_.playButton->setDisabled(true);
    ui_.resetButton->setDisabled(false);
    ui_.checkBox->setDisabled(true);
    ui_.resultLabel->clear();

    // Creathes a new head_ item
    const QPen black_pen(Qt::black, 0);
    const QBrush green_brush(Qt::green);
    head_ = scene_.addEllipse(0, 0, 1, 1, black_pen, green_brush);
    head_->setPos(10, 5);
    head_->setFlag(QGraphicsItem::ItemIsFocusable);
    head_->setFocus();

    // Starts both timers to move snake and take time and spawns first food
    adjustSceneArea();
    timer_.start(moveSpeed_);
    secTimer_.start(1000);
    spawnFood();
}

// Moves the snake head_ around
void MainWindow::moveSnake() {
    // Gets the current and new position for the head_
    const QPointF headPos = head_->scenePos();
    const QPointF newHeadPos = headPos + QPoint(xDir_, yDir_);

    // Moves the snakes body if there is one
    if ( snakeBody_.size() > 0 && !paused_ )
    {
        moveSnakeBody();
    }

    // This if - else if is for checking if the snake goes "around" the map
    if ( newHeadPos.x() < 0 )
    {
        head_->setPos(areaXSize_ - 1, head_->y());
        checkFoodCollision(head_->pos());
    }
    else if ( newHeadPos.x() > areaXSize_ - 1 )
    {
        head_->setPos(0, head_->y());
        checkFoodCollision(head_->pos());
    }
    else if ( newHeadPos.y() > areaYSize_ - 1 )
    {
        head_->setPos(head_->x(), 0);
        checkFoodCollision(head_->pos());
    }
    else if ( newHeadPos.y() < 0 )
    {
        head_->setPos(head_->x(), areaYSize_ - 1 );
        checkFoodCollision(head_->pos());
    }

    else
    {
        // If the snake collides to itself
        if ( checkSelfCollision(newHeadPos))
        {
            on_resetButton_clicked();   // GameOver
        }
        else
        {
            head_->setPos(newHeadPos);
            checkFoodCollision(head_->pos());
        }
    }
}

// Checks if the snake eats a food
void MainWindow::checkFoodCollision(QPointF newPos) {
    /* If the heads new position is same as foods position
     * adds points and displays it on the ui. Then calls
     * functions to grow the snake and spawn new food
     */
    if ( newPos == food_->pos() )
    {
        points_ += 1;
        ui_.points_lcdNumber->display(points_);
        scene_.removeItem(food_);
        growSnake();
        spawnFood();

        // Speeds the snake up every 5 points
        if ( points_ % 5 == 0 && moveSpeed_ > 100 )
        {
            moveSpeed_ -= 10;
            timer_.start(moveSpeed_);
        }
    }
}

// Checks if the snake hits itself
bool MainWindow::checkSelfCollision(QPointF newPos) {
    // Goes through every piece of snakes body
    for ( auto bodyPart : snakeBody_ )
    {
        // If the bodyparts position is same the snake dies
        if ( newPos == bodyPart->pos() )
        {
            return true;
        }
    }
    return false;
}

// Moves the rest of the snakes body
void MainWindow::moveSnakeBody() {
    prevPos_ = head_->pos();

    // Goes through every bodypart and sets its position to the next parts position
    for ( int i = 0; i < snakeBody_.size() - 1; i++ )
    {
        snakeBody_.at(i)->setPos(snakeBody_.at(i+1)->pos());
    }
    snakeBody_.last()->setPos(prevPos_);
}

// Fits the game scene to fit the window
void MainWindow::adjustSceneArea() {
    const QRectF area(0, 0, areaXSize_, areaYSize_ );
    scene_.setSceneRect(area);
    ui_.graphicsView->fitInView(area);
}

// Resets the game and acts as game over in the same time
void MainWindow::on_resetButton_clicked() {
    // Sets the ui component status' correctly
    ui_.resetButton->setDisabled(true);
    ui_.playButton->setDisabled(false);
    ui_.checkBox->setDisabled(false);
    ui_.checkBox->setChecked(false);

    // Updates the result message
    if ( !win_ )    // Game over
    {
        QString resultMessage = "Game Over!\n"
                                "Points: ";
        resultMessage.append(QString::number(points_));
        resultMessage.append("\nTime: ");
        resultMessage.append(QString::number(sec_));
        ui_.resultLabel->setText(resultMessage);
    }
    else            // Win
    {
        QString resultMessage = "You Win!\n"
                                "Congratulations!\n"
                                "Points: ";
        resultMessage.append(QString::number(points_));
        resultMessage.append("\nTime: ");
        resultMessage.append(QString::number(sec_));
        ui_.resultLabel->setText(resultMessage);
    }

    // Restores all the variable values to default and clears the scene_
    timer_.stop();      // Stops the snakes movement
    secTimer_.stop();   // Stops the time
    sec_ = 0;
    head_->setPos(9,5);
    xDir_ = 0;          // Resets the moving x direction
    yDir_ = 0;          // Resets the moving y direction
    lastDirection_ = 0;
    points_ = 0;
    ui_.points_lcdNumber->display(points_);
    ui_.time_lcdNumber->display(sec_);
    inverted_ = false;  // Inverted mode is chosen seperately each round

    // Destroys the GraphicsItems in scene_
    delete head_;
    delete food_;
    for ( auto i : snakeBody_ )
    {
        delete i;
    }
    snakeBody_.clear();
}

// Pauses and continues the game
void MainWindow::on_pauseButton_clicked() {
    // Checks that the game is running
    if ( !paused_ && !reseted_ )     // To pause the game
    {
        // Stops both timers and updates ui texts
        secTimer_.stop();
        timer_.stop();
        ui_.pauseButton->setText("Continue");
        ui_.resultLabel->setText("Paused");
        paused_ = true;
    }
    else              // To continue
    {
        // Starts both timers and updates ui texts
        secTimer_.start(1000);
        timer_.start(moveSpeed_);
        ui_.pauseButton->setText("Pause");
        ui_.resultLabel->clear();
        paused_ = false;
    }
}

// Spawns new food to a free location
void MainWindow::spawnFood() {
    const QPen black_pen(Qt::black, 0);
    const QBrush red_brush(Qt::red);

    // Randomizes the foods x and y cordinates
    foodX_ = random(0, areaXSize_);
    foodY_ = random(0, areaYSize_);

    food_ = scene_.addEllipse(0, 0, 1, 1, black_pen, red_brush);

    /* Checks that the food will not spawn to a location that has snake in it.
     * Otherwise randomizes the location again.
     */
    if ( foodX_ != head_->x() && foodY_ != head_->y() )
    {
        for (auto bodyPart : snakeBody_)
        {
            if ( foodX_ == bodyPart->x() && foodY_ == bodyPart->y() )
            {
                scene_.removeItem(food_);
                spawnFood();
            }
            else
            {
                food_->setPos(foodX_, foodY_);
            }
        }
    }
    else
    {
        scene_.removeItem(food_);
        spawnFood();
    }
}

// Creates a new body item to grow snake
void MainWindow::growSnake() {
    if (snakeBody_.size() + 1 == 200)  // Game won
    {
        win_ = true;
        on_resetButton_clicked();
    }
    else
    {
        QGraphicsEllipseItem* body_part = nullptr;
        const QPen black_pen(Qt::black, 0);
        const QBrush blue_brush(Qt::darkGreen);
        body_part = scene_.addEllipse(0,0,1,1,black_pen,blue_brush);

        // sets new bodypart outside the map so it doesn't blink in (0,0)
        body_part->setPos(-200, -200);
        snakeBody_.prepend(body_part);
    }
}

// Creates a random integren for the food to spawn
unsigned long int MainWindow::random(int from, int to) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<std::mt19937::result_type> dist(from, to-1);
    return dist(rng);
}

/* CheckBox to apply inverted control -mode
 * \param checked: boolean to show if the checkbox is toggled
 */
void MainWindow::on_checkBox_toggled(bool checked)
{
    if ( checked )
    {
        inverted_ = true;
    }
}

// Updates the timer to show playtime
void MainWindow::updateClock() {
    ++sec_;
    ui_.time_lcdNumber->display(sec_);
}
