/**
 * @file Game.h
 * @author Michal Mastej
 * @brief Game header file. Game is main class in which game tooks place.
 * @version 0.1
 * @date 2024-04-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QColor>
#include <QComboBox>
//#include <QGamepad>

#include "Player.h"
#include "Score.h"
#include "Health.h"
#include "ComboBoxTxt.h"
#include "ControllerManager.h"
#include "AxisPlot.h"

/**
 * @brief Main game class to controll events in the game.
 * 
 */

class Game : public QGraphicsView {
public:
    QGraphicsScene *scene;
    Player *player;
    Score *score;
    Health *health;
    ComboBoxTxt *difficulty, *language;
    ControllerManager *manager;
    AxisPlot *axises_plot;

    Game(QWidget *parent = 0);

    void drawPanel(const int x, const int y, const int width, const int height, const QColor color, const double opacity);
    void drawGUI();
    void comboBoxChange(int index, QComboBox &language);

    void resizeEvent(QResizeEvent *event);
public slots:
    void updateGraph();
};

#endif // GAME_H
