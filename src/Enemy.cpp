/**
 * @file Enemy.cpp
 * @author Michal Mastej
 * @brief Enemy source file. Contains constructor and move function.
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

#include "../inc/Enemy.h"
#include "../inc/Game.h"

extern Game *game;

/**
 * @brief Construct a new Enemy:: Enemy object
 * 
 */
Enemy::Enemy() {

    srand(time(NULL));

    int rand_numb = rand() % 700;
    setPos(rand_numb, 0);

    // setRect(0, 0, 100, 100);
    this->setPixmap(QPixmap(":/images/enemy.png"));
    this->setTransformOriginPoint(50, 60);
    this->setRotation(180);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    timer->start(50);
}

/**
 * @brief Function to set starting position of the Enemy and check for collision with player and screen boundries.
 * 
 */
void Enemy::move() {
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
