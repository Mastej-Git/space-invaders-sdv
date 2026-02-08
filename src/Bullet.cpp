/**
 * @file Bullet.cpp
 * @author Michal Mastej
 * @brief Source file for Bullet funtions. Contains constructor and move function.
 * @version 0.1
 * @date 2024-04-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <QTimer>
#include <QGraphicsScene>
#include <QList>

#include "../inc/Bullet.h"
#include "../inc/EnemyCyborg.h"
#include "../inc/Game.h"
#include "../inc/Score.h"
#include "../inc/Health.h"

extern Game *game;

/**
 * @brief Construct a new Bullet:: Bullet object
 * 
 */
Bullet::Bullet() {
    // setRect(50 - rect().width()/2, 0, 10, 40);
    setPixmap(QPixmap(":/images/bullet.png"));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    timer->start(50);
}


/**
 * @brief Function to move the Bullet and check for collision with other objects or boundries of the screen.
 * 
 */
void Bullet::move() {

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (auto elem : colliding_items) {

        if (typeid(*(elem)) == typeid(EnemyCyborg)) {

            game->score->increase();

            scene()->removeItem(elem);
            scene()->removeItem(this);

            delete elem;
            delete this;

            return;
        }

        else if (typeid(*(elem)) != typeid(EnemyCyborg) && typeid(*(elem)) != typeid(Player) && typeid(*(elem)) != typeid(Bullet)) {
            scene()->removeItem(this);
            delete this;

            return;
        }
    }

    setPos(x(), y() - 10);
    if (pos().y() + boundingRect().height() < 0) {
        scene()->removeItem(this);
        delete this;
    }
}
