/**
 * @file Score.h
 * @author Michal Mastej
 * @brief Score header file. Displays score points earned by player by shooting down enemys.
 * @version 0.1
 * @date 2024-04-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>
#include <QGraphicsView>

/**
 * @brief Cyan text in upper left corner indicating player score points.
 * 
 */

class Score: public QGraphicsTextItem {
private:
    int score;
public:
    int *language_ptr;

    Score(QGraphicsItem *parent = 0);
    void increase();
    int get_score();
};

#endif // SCORE_H
