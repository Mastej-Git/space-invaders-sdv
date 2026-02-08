/**
 * @file EnemyCyborg.h
 * @author Michal Mastej
 * @brief EnemyCyborg header file. Second enemy type that spawns randomly. Is weak to Bullet.
 * @version 0.1
 * @date 2024-04-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef ENEMYCYBORG_H
#define ENEMYCYBORG_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QObject>

/**
 * @brief Second enemy type that Player has to eliminate. Is weak to Bullet projectile.
 * 
 */

class EnemyCyborg : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    EnemyCyborg();
public slots:
    void move();
};

#endif // ENEMYCYBORG_H
