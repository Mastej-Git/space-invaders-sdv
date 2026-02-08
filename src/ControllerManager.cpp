#include <QDebug>
#include <QBrush>

#include "../inc/ControllerManager.h"

/**
 * @brief Construct a new Controller Manager:: Controller Manager object. Assigns indicator circle from the game gui
 * 
 * @param[out] indicator 
 */

ControllerManager::ControllerManager(QGraphicsEllipseItem *indicator) {
    this->controller_manager = QGamepadManager::instance();
    this->indicator = indicator;
}

/**
 * @brief Check for the controller connection 
 * 
 */

void ControllerManager::is_controller_connected() {
    if (this->controller_manager->connectedGamepads().count() > 0) {
        this->indicator->setBrush(Qt::green);

    }
    else {
        this->indicator->setBrush(Qt::red);
    }
}
