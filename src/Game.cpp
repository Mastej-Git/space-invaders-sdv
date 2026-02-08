/**
 * @file Game.cpp
 * @author Michal Mastej
 * @brief Game source file. Contains code for all the functions from header file.
 * @version 0.1
 * @date 2024-04-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <QTimer>
#include <QComboBox>
#include <QGraphicsProxyWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QMainWindow>
#include <QDebug>
#include <QtGamepad/QGamepad>
#include <QtGamepad/QGamepadManager>
#include <QTranslator>

#include "../inc/Game.h"
#include "../inc/qcustomplot.h"

/**
 * @brief Construct a new Game:: Game object. Crates and sets all the game components - scene, player, score, health, enemies, GUI. 
 * Also creates signals for enemy spawning, updating player position, updating player projectiles. 
 * 
 * @param[in] parent a parent widget
 */
Game::Game(QWidget *parent) {

    // create the scene
    this->scene = new QGraphicsScene();
    this->scene->setSceneRect(0, 0, 950, 600);

    // set the scene
    setScene(this->scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setBackgroundBrush(QColor("#050d33"));

    // translator

    QTranslator translator;
    translator.load(":/language/polish.tr");

    // create the player

    QGamepadManager *gamepad_manager = QGamepadManager::instance();
    QGamepad *gamepad = new QGamepad(3302);

    this->player = new Player(gamepad);
    this->player->setFlag(QGraphicsItem::ItemIsFocusable);
    this->player->setFocus();
    this->scene->addItem(this->player);

    // create the score
    this->score = new Score();
    this->scene->addItem(this->score);

    // create the health
    this->health = new Health();
    this->scene->addItem(this->health);

    // create the enemies
    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this->player, SLOT(spawn()));
    timer->start(2000);

    // update player position
    QTimer *timer1 = new QTimer();
    QObject::connect(timer1, SIGNAL(timeout()), this->player, SLOT(updatePlayerPosition()));
    timer1->start(20);

    // update player bullets
    QTimer *timer2 = new QTimer();
    QObject::connect(timer2, SIGNAL(timeout()), this->player, SLOT(updatePlayerBullets()));
    timer2->start(100);

    this->drawGUI();
}

/**
 * @brief Creates GUI background panel wothout any widgets.
 * 
 * @param[in] x GUI x posistion
 * @param[in] y GUI y position
 * @param[in] width GUI width
 * @param[in] height GUI height
 * @param[in] color GUI color
 * @param[in] opacity GUI opacity
 */
void Game::drawPanel(const int x, const int y, const int width, const int height, const QColor color, const double opacity) {

    QGraphicsRectItem *panel = new QGraphicsRectItem(x, y, width, height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}

/**
 * @brief Draws all the GUI widgets - controller indicator circle, difficulty ComboBoxTxt, language ComboBoxTxt, and all the texts. 
 * 
 */
void Game::drawGUI() {
    this->drawPanel(800, 0, 150, 600, Qt::black, 1);

    // controller indicator circle
    QGraphicsEllipseItem *connection_indicator = new QGraphicsEllipseItem(810, 12, 20, 20);
    connection_indicator->setBrush(Qt::green);
    connection_indicator->setPen(QPen(Qt::white, 2));

    scene->addItem(connection_indicator);

    this->manager = new ControllerManager(connection_indicator);

    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this->manager, SLOT(is_controller_connected()));
    timer->start(20);

    // controller indicator text
    QGraphicsTextItem *controller_text = new QGraphicsTextItem(QObject::tr("Controller"));
    controller_text->setPos(835, 8);
    controller_text->setDefaultTextColor(Qt::white);

    QFont controller_font("Times[Adobe]", 12);
    controller_font.setBold(true);
    controller_text->setFont(controller_font);

    scene->addItem(controller_text);

    // plot
    this->axises_plot = new AxisPlot(this->player);

    QTimer *dataTimer = new QTimer(this);
    QObject::connect(dataTimer, SIGNAL(timeout()), this->axises_plot, SLOT(updateGraph()));
    dataTimer->start(100);

    QGraphicsProxyWidget *proxy3 = scene->addWidget(this->axises_plot->plot);
    proxy3->setPos(810, 70);

    // difficulty combobox and txt
    QStringList list = {"Easy", "Medium", "Hard"};
    this->difficulty = new ComboBoxTxt(list, "Difficulty level", 807, 277, this->health, this->score, this->player, nullptr);

    QGraphicsProxyWidget *proxy1 = scene->addWidget(this->difficulty->combo_box);
    proxy1->setPos(810, 300);
    scene->addItem(this->difficulty->text);

    QObject::connect(this->difficulty->combo_box, SIGNAL(currentIndexChanged(int)), this->difficulty, SLOT(change_item(int)));

    // language combobox and txt

    QGraphicsTextItem **txts_table = new QGraphicsTextItem*[5];
    txts_table[0] = controller_text;
    txts_table[1] = this->difficulty->text;

    QStringList list1 = {"English", "Polski"};
    this->language = new ComboBoxTxt(list1, "Language", 807, 517, this->health, this->score, this->player, txts_table);

    QGraphicsProxyWidget *proxy2 = scene->addWidget(this->language->combo_box);
    proxy2->setPos(810, 540);
    scene->addItem(this->language->text);

    QObject::connect(this->language->combo_box, SIGNAL(currentIndexChanged(int)), this->language, SLOT(change_language(int)));

    this->health->language_ptr = &(this->language->index);
    this->score->language_ptr = &(this->language->index);
}

/**
 * @brief Helps scaling and rezising window
 * @param event
 */

void Game::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    fitInView(sceneRect(), Qt::KeepAspectRatio);
}
