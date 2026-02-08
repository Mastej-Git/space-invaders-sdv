/**
 * @file EnemySentients.h
 * @author Michal Mastej
 * @brief EnemySentients header file. Third type of enemy that spawns randomly in the game. Is weak to Laser.
 * @version 0.1
 * @date 2024-04-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef ENEMYSENTIENTS_H
#define ENEMYSENTIENTS_H

#include <QGraphicsPixmapItem>
#include <QObject>

/**
 * @brief Third enemy type that Player has to eliminate. Is weak to Laser weapon.
 * 
 */

class EnemySentients : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    EnemySentients();
public slots:
    void move();
};

#endif // ENEMYSENTIENTS_H
