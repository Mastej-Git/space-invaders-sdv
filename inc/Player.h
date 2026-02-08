/**
 * @file Player.h
 * @author Michal Mastej
 * @brief Player header file. Player is controllabe character that user can play. It can shot at move.
 * @version 0.1
 * @date 2024-04-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QtGamepad/QGamepad>

/**
 * @brief Main Player class to controll player and handle all events connectes to his movement.
 * 
 */

class Player : public QObject, public QGraphicsPixmapItem  {
    Q_OBJECT
public:

    QGamepad *gamepad;

    bool keyLeftPressed;
    bool keyRightPressed;
    bool keyUpPressed;
    bool keyDownPressed;
    bool keySpacebarPressed;
    bool keyFlamePressed;
    bool keyLaserPressed;

    double xAxisValue;
    double yAxisValue;

    Player(QGamepad *gamepad);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void gamepadPressEvent();

public slots:
    void spawn();
    void updatePlayerPosition ();
    void updatePlayerBullets ();


    void handleButtonLeftChange();
    void handleButtonRightChange();
    void handleButtonUpChange();
    void handleButtonDownChange();

    void handleButtonXChange();
    void handleButtonSqChange();
    void handleButtonTrChange();

    void handleXAxisLeftThumbstick(const double value);
    void handleYAxisLeftThumbstick(const double value);
};

#endif // MYRECT_H
