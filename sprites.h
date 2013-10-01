#ifndef SPRITES_H
#define SPRITES_H
#include <QGraphicsPixmapItem>
class Item: public QGraphicsPixmapItem
{
public:
    enum{BOX=UserType+10,WALL,MAN,DESTINATION};
    static const int WIDTH = 40;
    static const int HEIGHT = 40;
    Item(QPixmap &pic):QGraphicsPixmapItem(pic){}
protected:
};
class Wall: public Item
{
public:
    Wall(QPixmap &pic):Item(pic){setData(0,"wall");setZValue(2);}
    int type() const {return WALL;}
};

class Box: public Item
{
public:
    Box(QPixmap &outbox,QPixmap &inbox):Item(outbox),outPixmap(outbox),inPixmap(inbox){setData(0,"box");setData(1,false);setZValue(2);}
    void out(){ setPixmap(outPixmap);}
    void in(){ setPixmap(inPixmap);}
//   int type() const {return BOX;}
private:
    QPixmap &outPixmap;
    QPixmap &inPixmap;
};

class Destination: public Item
{
public:
    Destination(QPixmap &pic):Item(pic){setData(0,"destination");setZValue(0);}
    int type() const {return DESTINATION;}
};

class BoxMan: public Item
{
public:
    BoxMan(QPixmap &pic):Item(pic){setData(0,"boxman");setZValue(2);}
    int type() const {return MAN;}
};
class Floor: public Item
{
public:
    Floor(QPixmap &pic):Item(pic){setData(0,"floor");setZValue(0);}
};

#endif // SPRITES_H
