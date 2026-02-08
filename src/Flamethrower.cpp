/**
 * @file Flamethrower.cpp
 * @author Michal Mastej
 * @brief Flamethrower weapon source file. Contains code for all the functions from header file.
 * @version 0.1
 * @date 2024-04-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <QTimer>
#include <QGraphicsScene>
#include <QList>

#include "../inc/Flamethrower.h"
#include "../inc/Enemy.h"
#include "../inc/Game.h"

extern Game *game;

/**
 * @brief Construct a new Flamethrower:: Flamethrower object
 * 
 * @param[in] x_move describes which way should the Flamethrower particle go on X axis
 * @param[in] y_move describes which way should the Flamethrower particle go on Y axis
 */
Flamethrower::Flamethrower(const double x_move, const double y_move) {
    setPixmap(QPixmap(":/images/flame.png"));
//    setRect(50 - rect().width()/2, 0, 10, 10);
//    setPos(45, 0);

/**
 * @brief Assigns the pixmap, position and timer
 * 
 */
    this->x_move = x_move;
    this->y_move = y_move;
    this->time = 0;

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    timer->start(50);
}

/**
 * @brief Function to move the Flamthrower and check for collision with other objects or boundries of the screen.
 * 
 */
void Flamethrower::move() {

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (auto elem : colliding_items) {

        if (typeid(*(elem)) == typeid(Enemy)) {

            game->score->increase();

            scene()->removeItem(elem);
            scene()->removeItem(this);

            delete elem;
            delete this;

            return;
        }
        else if (typeid(*(elem)) != typeid(Enemy) && typeid(*(elem)) != typeid(Player) && typeid(*(elem)) != typeid(Flamethrower)) {
            scene()->removeItem(this);
            delete this;

            return;
        }
    }

    setPos(x() + this->x_move, y() + this->y_move);
    if (pos().y() + 10 < 0 || pos().y() > 600 || pos().x() + 10 < 0 || pos().x() > 800) {
        scene()->removeItem(this);
        delete this;
    }

    this->time += 50;
    if(this->time == 1200){
        scene()->removeItem(this);
        delete this;
    }
}
