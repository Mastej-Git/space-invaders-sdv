/**
 * @file Player.cpp
 * @author Michal Mastej
 * @brief Player source file. Contains code for all the functions from header file.
 * @version 0.1
 * @date 2024-04-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include <QtGamepad/QGamepad>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "../inc/Player.h"
#include "../inc/Bullet.h"
#include "../inc/Flamethrower.h"
#include "../inc/Laser.h"
#include "../inc/Enemy.h"
#include "../inc/EnemyCyborg.h"
#include "../inc/EnemySentients.h"

/**
 * @brief Construct a new Player:: Player object. Sets all the key flags to false and connects the gamepad
 * 
 * @param[in] gamepad gamepad pointer to read axis values
 */
Player::Player(QGamepad *gamepad) {

    this->setPixmap(QPixmap(":/images/player_ship.png"));
    this->setPos(800/2 - 50, 600 - 100);

    this->keyLeftPressed = false;
    this->keyRightPressed = false;
    this->keyUpPressed = false;
    this->keyDownPressed = false;
    this->keySpacebarPressed = false;
    this->keyFlamePressed = false;
    this->keyLaserPressed = false;

    this->gamepad = gamepad;
}

/**
 * @brief Listens and sets the key flags to true on press and reads the controller inputs
 * 
 * @param[in] event event variable indicating any event in the app, like button press.
 */
void Player::keyPressEvent(QKeyEvent *event) {
    connect(this->gamepad, &QGamepad::buttonLeftChanged, this, &Player::handleButtonLeftChange);
    connect(this->gamepad, &QGamepad::buttonRightChanged, this, &Player::handleButtonRightChange);
    connect(this->gamepad, &QGamepad::buttonUpChanged, this, &Player::handleButtonUpChange);
    connect(this->gamepad, &QGamepad::buttonDownChanged, this, &Player::handleButtonDownChange);

    connect(this->gamepad, &QGamepad::buttonAChanged, this, &Player::handleButtonXChange);
    connect(this->gamepad, &QGamepad::buttonXChanged, this, &Player::handleButtonTrChange);
    connect(this->gamepad, &QGamepad::buttonYChanged, this, &Player::handleButtonSqChange);

    connect(this->gamepad, &QGamepad::axisLeftXChanged, this, &Player::handleXAxisLeftThumbstick);
    connect(this->gamepad, &QGamepad::axisLeftYChanged, this, &Player::handleYAxisLeftThumbstick);

    if (event->key() == Qt::Key_Left) {
        this->keyLeftPressed = true;
    } else if (event->key() == Qt::Key_Right) {
        this->keyRightPressed = true;
    } else if (event->key() == Qt::Key_Up) {
        this->keyUpPressed = true;
    } else if (event->key() == Qt::Key_Down) {
        this->keyDownPressed = true;
    } else if (event->key() == Qt::Key_Z) {
        this->keySpacebarPressed = true;
    } else if (event->key() == Qt::Key_X) {
        this->keyFlamePressed = true;
    } else if (event->key() == Qt::Key_C) {
        this->keyLaserPressed = true;
    }
}

/**
 * @brief Listens and sets the key flags to false on release
 * 
 * @param[in] event 
 */
void Player::keyReleaseEvent(QKeyEvent *event) {
    // Clear flags when keys are released
    if (event->key() == Qt::Key_Left || gamepad->buttonLeft()) {
        this->keyLeftPressed = false;
//        qDebug() << "Controller key released";
    } else if (event->key() == Qt::Key_Right) {
        this->keyRightPressed = false;
    } else if (event->key() == Qt::Key_Up) {
        this->keyUpPressed = false;
    } else if (event->key() == Qt::Key_Down) {
        this->keyDownPressed = false;
    } else if (event->key() == Qt::Key_Z) {
        this->keySpacebarPressed = false;
    } else if (event->key() == Qt::Key_X) {
        this->keyFlamePressed = false;
    } else if (event->key() == Qt::Key_C) {
        this->keyLaserPressed = false;
    }
}

void Player::gamepadPressEvent() {
    connect(this->gamepad, &QGamepad::buttonLeftChanged, this, &Player::handleButtonLeftChange);
    connect(this->gamepad, &QGamepad::buttonRightChanged, this, &Player::handleButtonRightChange);
    connect(this->gamepad, &QGamepad::buttonUpChanged, this, &Player::handleButtonUpChange);
    connect(this->gamepad, &QGamepad::buttonDownChanged, this, &Player::handleButtonDownChange);
}
/**
 * @brief Slot function to move the Player
 * 
 */
void Player::updatePlayerPosition() {
    int dx = 0;
    int dy = 0;

    // Calculate movement in both x and y directions
    if (keyLeftPressed  && pos().x() > 0) {
        dx -= 5;
    }
    if (keyRightPressed && pos().x() + 100 < 800) {
        dx += 5;
    }
    if (keyUpPressed && pos().y() > 0) {
        dy -= 5;
    }
    if (keyDownPressed && pos().y() + 100 < 600) {
        dy += 5;
    }

    // Update player position
    setPos(x() + dx, y() + dy);
}

/**
 * @brief Slot function to move the bullets
 * 
 */
void Player::updatePlayerBullets() {
    if (keySpacebarPressed) {
        Bullet *bullet = new Bullet();
        bullet->setPos(x(), y());
        // bullet->setBrush(Qt::yellow);
        scene()->addItem(bullet);
    }

    if (keyFlamePressed) {
        Flamethrower **flamethrower = new Flamethrower*[5];
        flamethrower[0] = new Flamethrower(-5, -3);
        flamethrower[1] = new Flamethrower(-3, -5);
        flamethrower[2] = new Flamethrower(0, -5);
        flamethrower[3] = new Flamethrower(3, -5);
        flamethrower[4] = new Flamethrower(5, -3);

        for (int i = 0; i < 5; ++i) {
            flamethrower[i]->setPos(x() + 46, y());
            scene()->addItem((flamethrower[i]));
        }
    }

    if (keyLaserPressed) {
        Laser *laser = new Laser();
        laser->setPos(x(), y());
        laser->setBrush(Qt::magenta);
        scene()->addItem(laser);
    }
}

/**
 * @brief Slot position to spawn all the enemy types
 * 
 */
void Player::spawn() {

    int rand_numb = rand() % 3 + 1;

    if (rand_numb == 1) {
        Enemy *enemy = new Enemy();
        // enemy->setBrush(Qt::blue);
        scene()->addItem(enemy);
    }
    else if (rand_numb == 2) {
        EnemyCyborg *cyborg_enemy = new EnemyCyborg();
//        cyborg_enemy->setBrush(Qt::lightGray);
        scene()->addItem(cyborg_enemy);
    }
    else if (rand_numb == 3) {
        EnemySentients *sentient_enemy = new EnemySentients();
//        sentient_enemy->setBrush(Qt::darkRed);
        scene()->addItem(sentient_enemy);
    }

}

/**
 * @brief Player::handleButtonLeftChange Signal to change the Left controll state (true/false)
 */

void Player::handleButtonLeftChange() {
    this->keyLeftPressed == true ? this->keyLeftPressed = false : this->keyLeftPressed = true;
}

/**
 * @brief Player::handleButtonRightChange Signal to change the Right controll state (true/false)
 */

void Player::handleButtonRightChange() {
    this->keyRightPressed == true ? this->keyRightPressed = false : this->keyRightPressed = true;
}

/**
 * @brief Player::handleButtonUpChange Signal to change the Up controll state (true/false)
 */

void Player::handleButtonUpChange() {
    this->keyUpPressed == true ? this->keyUpPressed = false : this->keyUpPressed = true;
}

/**
 * @brief Player::handleButtonDownChange Signal to change the Down controll state (true/false)
 */

void Player::handleButtonDownChange() {
    this->keyDownPressed == true ? this->keyDownPressed = false : this->keyDownPressed = true;
}

/**
 * @brief Player::handleButtonXChange Signal to change the fire Bullet controll state (true/false)
 */

void Player::handleButtonXChange() {
    this->keySpacebarPressed == true ? this->keySpacebarPressed = false : this->keySpacebarPressed = true;
}

/**
 * @brief Player::handleButtonSqChange Signal to change the fire Flamethrower controll state (true/false)
 */

void Player::handleButtonSqChange() {
    this->keyFlamePressed == true ? this->keyFlamePressed = false : this->keyFlamePressed = true;
}

/**
 * @brief Player::handleButtonTrChange Signal to change the fire Laser controll state (true/false)
 */

void Player::handleButtonTrChange() {
    this->keyLaserPressed == true ? this->keyLaserPressed = false : this->keyLaserPressed = true;
}

/**
 * @brief Player::handleXAxisLeftThumbstick Signal to read the X axis thumbstick value
 * @param[in] value thumbstick value (-1.0 - 1.0)
 */

void Player::handleXAxisLeftThumbstick(const double value) {
    this->xAxisValue = value;

    if (value > 0.5) {
       this->keyRightPressed = true;
    }
    else if (value < 0.5 && value > -0.5) {
        this->keyRightPressed = false;
        this->keyLeftPressed = false;
    }
    else if (value < -0.5) {
        this->keyLeftPressed = true;
    }
}

/**
 * @brief Player::handleYAxisLeftThumbstick Signal to read the X axis thumbstick value
 * @param[in] value thumbstick value (-1.0 - 1.0)
 */

void Player::handleYAxisLeftThumbstick(const double value) {
    this->yAxisValue = value;

    if (value > 0.5) {
       this->keyDownPressed = true;
    }
    else if (value < 0.5 && value > -0.5) {
        this->keyDownPressed = false;
        this->keyUpPressed = false;
    }
    else if (value < -0.5) {
        this->keyUpPressed = true;
    }
}
