#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QDebug>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QTimer>
#include <QTransform>

class Game : public QWidget
{
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);
    ~Game();

    void keyPressEvent(QKeyEvent *event);

    void paintEvent(QPaintEvent *event);

    void show_Orientation(const int &key_id);//向方向上移动
private:
    QPoint location;
    int w, h, add_x, add_y, id_timer, key_id;//buff记录豆豆，可以提升移动速度

    QPixmap player;
};
#endif // GAME_H
