/**
 * @file Enemy.h
 * @author Michal Mastej
 * @brief Enemy header file. Basic enemy type that spawns randomly and is weak to Flamethrower.
 * @version 0.1
 * @date 2024-04-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QObject>

/**
 * @brief Basic enemy type that player has to eliminate. Is weak to Flamethrower weapon.
 * 
 */

class Enemy : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Enemy();
public slots:
    void move();
};

#endif // ENEMY_H
