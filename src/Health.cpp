/**
 * @file Health.cpp
 * @author Michal Mastej
 * @brief Health source file. Contains code for all the functions from header file.
 * @version 0.1
 * @date 2024-04-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <QFont>

#include "../inc/Health.h"

/**
 * @brief Construct a new Health:: Health object
 * 
 * @param[in] parent 
 */
Health::Health(QGraphicsItem *parent): QGraphicsTextItem(parent) {
    this->health = 5;
    this->language_ptr = nullptr;

    // draw the text
    setPlainText(QString("Health: ") + QString::number(this->health));
    setPos(0, 25);
    setDefaultTextColor(Qt::red);
    setFont(QFont("Times[Adobe]", 16));
}

/**
 * @brief Decreases health when any enemy type touches the Player.
 * 
 */
void Health::decrease() {
    this->health--;
    if (*(this->language_ptr) == 0) {
        setPlainText(QString("Health: ") + QString::number(this->health));
    }
    else {
        setPlainText(QString("Zdrowie: ") + QString::number(this->health));
    }
}

/**
 * @brief Returns health points
 * 
 * @return int health points value
 */
int Health::get_health() {
    return this->health;
}

/**
 * @brief Sets health points
 * 
 * @param[out] health parameter to set
 */
void Health::set_heath(int health) {
    this->health = health;
    setPlainText(QString("Health: ") + QString::number(this->health));
}
