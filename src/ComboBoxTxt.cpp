/**
 * @file ComboBoxTxt.cpp
 * @author Michal Mastej
 * @brief ComboBoxTxt source file. Contains contructor, change_item and change_language slots
 * @version 0.1
 * @date 2024-04-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../inc/ComboBoxTxt.h"
#include "QDebug"

/**
 * @brief Construct a new Combo Box Txt:: Combo Box Txt object
 * 
 * @param[in] list List of object that should be contained by the ComboBox
 * @param[in] text Text Displayed above ComboBox
 * @param[in] x ComboBox x position
 * @param[in] y ComboBox y position
 * @param[in, out] health Health pointer to change the health points
 * @param[in, out] player Player pointer to return focus on the player character
 */
ComboBoxTxt::ComboBoxTxt(const QStringList &list, const QString text, const int x, const int y, Health *health, Score *score, Player *player, QGraphicsTextItem **texts_table) {

    this->combo_box = new QComboBox();

    for (auto item : list) {
        this->combo_box->addItem(item);
    }

    QFont text_font("Times[Adobe]", 12);
    text_font.setBold(true);

    this->combo_box->setFont(text_font);
    this->combo_box->setStyleSheet("QComboBox { border: 2px solid grey; }");
    this->combo_box->setFixedWidth(130);

    this->text = new QGraphicsTextItem(text);
    this->text->setPos(x, y);
    this->text->setDefaultTextColor(Qt::white);
    this->text->setFont(QFont("Times[Adobe]", 9));

    this->health = health;
    this->score = score;
    this->player = player;

    this->texts_table = texts_table;

    this->index = 0;
}

/**
 * @brief Signal function to obatin index of the chosen item from difficulty ComboBoxTxt
 * 
 * @param[in] index Index of the chosen item.
 */
void ComboBoxTxt::change_item(int index) {
    if (index == 0) {
        this->health->set_heath(5);
    }
    else if (index == 1) {
        this->health->set_heath(3);
    }
    else {
        this->health->set_heath(1);
    }
    this->player->setFocus();
}

/**
 * @brief Signal function to obatin index of the chosen item from language ComboBoxTxt
 * 
 * @param[in] index index of the chosen item.
 */
void ComboBoxTxt::change_language(int index) {
    if (index == 1) {
//        qDebug() << "Zmieniono język na Polski";
        this->index = 1;
        this->health->setPlainText(QString("Zdrowie: ") + QString::number(this->health->get_health()));
        this->score->setPlainText(QString("Punkty: ") + QString::number(this->score->get_score()));
        this->text->setPlainText(QString("Jezyk"));
        this->texts_table[0]->setPlainText(QString("Kontroler"));
        this->texts_table[1]->setPlainText(QString("Poziom trudnosci"));
    }
    else {
        this->index = 0;
//        qDebug() << "Changed language to english";
        this->health->setPlainText(QString("Health: ") + QString::number(this->health->get_health()));
        this->score->setPlainText(QString("Score: ") + QString::number(this->score->get_score()));
        this->text->setPlainText(QString("Language"));
        this->texts_table[0]->setPlainText(QString("Controller"));
        this->texts_table[1]->setPlainText(QString("Difficulty level"));
    }

    this->player->setFocus();
}
