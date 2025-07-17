#include "game.h"
#define MAXW 600
#define MAXH 600

Game::Game(QWidget *parent)
    : QWidget(parent)
{
    location.setX(0);
    location.setY(0);
    w = h = 50;
    add_x = 20;
    add_y = 20;

    QPixmap path(":/game_img/1.png");
    player = path;
    this->setFixedSize(MAXW,MAXH);
}

Game::~Game()
{
}

void Game::keyPressEvent(QKeyEvent *event)
{
    key_id = event->key();
    show_Orientation(key_id);
    update();
}

void Game::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(location.rx(),location.ry(),w,h,player);
}

//先把豆豆能够正常的前后左右移动
void Game::show_Orientation(const int &key_id)
{
    QTransform form;
    QPixmap map(":/game_img/1.png");
    int x, y;
    switch (key_id) {
    case Qt::Key_Up:

        form.rotate(90);
        y = (location.ry()-add_y)%(MAXH-h);
        if(y > (MAXH-h))
            y =0;
        else if(y < 0)
            y = MAXH-h;

        location.setY(y);
        break;

    case Qt::Key_Down:
        form.rotate(270);
        y = (location.ry()+add_y)%(MAXH-h);

        if(y > (MAXH-h))
            y = 0;
        else if(y < 0)
            y = MAXH-h;

        location.setY(y);
        break;

    case Qt::Key_Left:
        form.rotate(360);
        x = (location.rx()-add_x)%(MAXW-w);

        if(x > (MAXW-w))
            x = 0;
        else if(x < 0)
            x = MAXW-w;

        location.setX(x);
        break;

    case Qt::Key_Right:
        form.rotate(180);
        x = (location.rx()+add_x)%(MAXW-w);

        if(x > (MAXW-w))
            x = 0;
        else if(x < 0)
            x = MAXW-w;

        location.setX(x);
        break;

    default:
        break;
    }

    player = map.transformed(form);
}
