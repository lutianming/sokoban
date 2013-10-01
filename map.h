#ifndef MAP_H
#define MAP_H
#include <QGraphicsScene>
#include <vector>
#include "sprites.h"
class SokobanView: public QWidget
{
public:
    SokobanView();
    void setBoxMan(BoxMan boxman);
private:
    QGraphicsScene scene;
    BoxMan boxman;
};

#endif // MAP_H
