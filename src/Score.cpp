/**
 * @file Score.cpp
 * @author Michal Mastej
 * @brief Score weapon source file. Contains code for all the functions from header file.
 * @version 0.1
 * @date 2024-04-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <QFont>

#include "../inc/Score.h"

/**
 * @brief Construct a new Score:: Score object
 * 
 * @param[in] parent 
 */
Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent) {
    this->score = 0;
    this->language_ptr = nullptr;

    // draw the text
    setPlainText(QString("Score: ") + QString::number(this->score));
    setDefaultTextColor(Qt::cyan);
    QGraphicsTextItem::setFont(QFont("Times[Adobe]", 16));
}

/**
 * @brief Returns health number
 * 
 */
void Score::increase() {
    this->score += 10;
    if (*(this->language_ptr) == 0) {
        setPlainText(QString("Score: ") + QString::number(this->score));
    }
    else {
        setPlainText(QString("Punkty: ") + QString::number(this->score));
    }
}

/**
 * @brief Sets health points
 * 
 * @return score points value
 */
int Score::get_score() {
    return this->score;
}
