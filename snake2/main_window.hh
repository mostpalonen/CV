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
# File: main_window.hh                                             #
# Description: Declares a class implementing a UI for the game.    #
#                                                                  #
# Author: Joonas Palonen, 272784, joonas.palonen@tuni.fi           #
####################################################################
*/

#ifndef PRG2_SNAKE2_MAINWINDOW_HH
#define PRG2_SNAKE2_MAINWINDOW_HH

#include "ui_main_window.h"
#include <QGraphicsScene>
#include <QMainWindow>
#include <QTimer>
#include <random>
#include <vector>

/* \class MainWindow
 * \brief Implements the main window through which the game is played.
 */
class MainWindow: public QMainWindow {
    Q_OBJECT

public:

    /* \brief Construct a MainWindow.
     * \param[in] parent The parent widget of this MainWindow.
     */
    explicit MainWindow(QWidget* parent = nullptr);

    /* \brief Destruct a MainWindow.
     */
    ~MainWindow() override = default;

    /* \brief Change the Snake's bearing when certain keys get pressed.
     * \param[in] event Contains data on pressed and released keys.
     */
    void keyPressEvent(QKeyEvent* event) override;

private slots:

    /* \brief Start the game.
     */
    void on_playButton_clicked();

    /* \brief Move the Snake by a square and check for collisions.
     * The game ends if the Snake itself gets in the way.
     * When a food gets eaten a point is gained and the Snake grows.
     */
    void moveSnake();

    // Resets the game and acts as a GameOver
    void on_resetButton_clicked();

    // Pauses and resumes the game
    void on_pauseButton_clicked();

    // CheckBox to apply inverted control -mode
    void on_checkBox_toggled(bool checked);

private:

    /* \brief Variable used to store the last moving direction of the snake
     * 1 = UP, 2 = DOWN, 3 = RIGHT, 4 = LEFT
     */
    int lastDirection_ = 0;

    /* \brief Variables used to store the x and y direction of the snakes
     * movement
     */
    uint xDir_ = 0;
    uint yDir_ = 0;

    // X and Y coordinate for the food to spawn in
    int foodX_;
    int foodY_;

    // Default size of the play area
    int areaXSize_ = 20;
    int areaYSize_ = 10;

    int moveSpeed_ = 200;                  // The move speed if the snake
    int points_ = 0;                       // Tells the points and the length of the snake
    bool paused_ = false;                  // To check if game is paused
    bool reseted_ = false;                 // To check if game is reseted
    bool inverted_ = false;                // To check if controls are inverted
    bool win_ = false;
    int sec_ = 0;                          // Time passed in a round


    /* \brief Make the play field visible and fit it into the view.
     * Should be called every time the field's size changes.
     */
    void adjustSceneArea();

    // Updates the timer to show playtime. Is called every second
    void updateClock();

    // Creates a new body item to grow snake. Is called every time the snake eats food
    void growSnake();

    // Spawns new food to a free location. Is called every time a food is eaten
    void spawnFood();

    // Moves the rest of the snakes body. Is called every time the timer_ timeouts
    void moveSnakeBody();

    // Checks if the snake eats a food. Is called every time the snake moves
    void checkFoodCollision(QPointF newPos);

    // Checks if the snake hits itself. Is called every time the snake moves
    bool checkSelfCollision(QPointF newPos);

    // Creates a random integren for the food to spawn
    unsigned long int random(int from, int to);

    Ui::MainWindow ui_;                     // Accesses the UI widgets.
    QGraphicsEllipseItem* food_ = nullptr;  // The food item in the scene.
    QGraphicsEllipseItem* head_ = nullptr;  // The head of the snake in the scene.
    QGraphicsScene scene_;                  // Manages drawable objects.
    QTimer timer_;                          // Triggers the Snake to move.
    QTimer secTimer_;                       // Takes the time passed in a round.
    std::default_random_engine rng_;        // Randomizes food locations.

    QList<QGraphicsEllipseItem*> snakeBody_; // List to store all the bodyparts

    QPointF prevPos_;           // Used to store previous position of a snake part
    QString resultMessage = ""; // String to store the endgame result text

};  // class MainWindow


#endif  // PRG2_SNAKE2_MAINWINDOW_HH
