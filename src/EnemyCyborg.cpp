/**
 * @file EnemyCyborg.cpp
 * @author Michal Mastej
 * @brief EnemyCyborg source file. Contains code for all the functions from header file.
 * @version 0.1
 * @date 2024-04-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h>
#include <time.h>

#include "../inc/EnemyCyborg.h"
#include "../inc/Game.h"

extern Game *game;

/**
 * @brief Construct a new Enemy Cyborg:: Enemy Cyborg object
 * 
 */
EnemyCyborg::EnemyCyborg() {

    srand(time(NULL));

    int rand_numb = rand() % 700;
    setPos(rand_numb, 0);

    // setRect(0, 0, 65, 140);
    this->setPixmap(QPixmap(":/images/enemy_cyborg.png"));
    this->setTransformOriginPoint(50, 60);
    this->setRotation(180);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    timer->start(50);
}

/**
 * @brief Function to set starting position of the EnemyCyborg and check for collision with player and screen boundries.
 * 
 */
void EnemyCyborg::move() {
    setPos(x(), y() + rand() % 5 + 3);

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (auto elem : colliding_items) {
        if (typeid(*(elem)) == typeid(Player)) {

            game->health->decrease();
            scene()->removeItem(this);
            delete this;

            return;
        }
    }

    if (pos().y() > 600) {
        game->health->decrease();
        scene()->removeItem(this);
        delete this;
    }
}
