#include "sokobanview.h"
#include <QFileInfo>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QDropEvent>
#include <QDragEnterEvent>
SokobanView::SokobanView(QWidget *parent) :
        QWidget(parent),mapScene(0,0,Item::WIDTH*19,Item::HEIGHT*15),view(&mapScene,this),editting(false)
{    
    view.setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    view.setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setOptimizationFlags(QGraphicsView::DontClipPainter
                              | QGraphicsView::DontSavePainterState
                              | QGraphicsView::DontAdjustForAntialiasing);
    view.viewport()->setFocusProxy( this );
    view.setAcceptDrops(false);
    mapScene.setBackgroundBrush(QPixmap(":/images/empty.jpg"));
    setAcceptDrops(true);
    setFixedSize(Item::WIDTH*19,Item::HEIGHT*15);
    resetInfo();
    QGraphicsTextItem *gameName = new QGraphicsTextItem("Sokoban");
    gameName->setDefaultTextColor(Qt::blue);
    QFont font("Arial",60,QFont::Bold,true);
    font.setUnderline(true);
    font.setOverline(true);
    font.setLetterSpacing(QFont::AbsoluteSpacing,10);
    gameName->setFont(font);
    gameName->setPos(200,200);
    mapScene.addItem(gameName);
}

void SokobanView::resetInfo(int level)
{
    this->level = level;
    this->stepCount = 0;
    this->inPlaceCount = 0;
    this->desCount = 0;
    mapScene.clear();
}

void SokobanView::checkWin()
{
    if(inPlaceCount == desCount){
        emit win();
    }

}
void SokobanView::boxIn(QGraphicsItem *box)
{
    if(box->data(1) == false){
        box->setData(1,true);
        (qgraphicsitem_cast<Box*>(box))->in();
        inPlaceCount++;
    }

}
void SokobanView::boxOut(QGraphicsItem *box)
{
    if(box->data(1) == true){
        box->setData(1,false);
        (qgraphicsitem_cast<Box*>(box))->out();
        inPlaceCount--;
    }
}
void SokobanView::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("image/x-mapItem")) {

        QByteArray pieceData = event->mimeData()->data("image/x-mapItem");
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
        QPixmap pixmap;
        QString name;
        dataStream >> pixmap >> name;
        event->setDropAction(Qt::MoveAction);
        event->accept();
        QPoint pos = event->pos();
        int x = pos.x()/Item::WIDTH * Item::WIDTH;
        int y = pos.y()/Item::HEIGHT * Item::HEIGHT;
        Item *item = 0;
        if(name == "box"){
            item = new Box(pixmap,pixmap);
//            box->setPos(x,y);
//            mapScene.addItem(box);
        }else if(name == "destination"){
            item = new Destination(pixmap);
 //           des->setPos(x,y);
 //           mapScene.addItem(des);
        }else if(name == "boxman"){
            item = new BoxMan(pixmap);
 //           man->setPos(x,y);
 //           mapScene.addItem(man);
        }else if(name == "wall"){
            item = new Wall(pixmap);
 //           wall->setPos(x,y);
 //           mapScene.addItem(wall);
        }else if(name == "floor"){
            item = new Floor(pixmap);
//            floor->setPos(x,y);
//            mapScene.addItem(floor);
        }
        QGraphicsItem *itemOnMap = mapScene.itemAt(x,y);
        if( itemOnMap != 0 && itemOnMap->zValue() == item->zValue())
            mapScene.removeItem(itemOnMap);
        item->setPos(x,y);
        mapScene.addItem(item);
        changed = true;
    } else {
        event->ignore();
    }
}

void SokobanView::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("image/x-mapItem"))
        event->accept();
    else
        event->ignore();
}

void SokobanView::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && editting){
        QPoint pos = event->pos();
        QGraphicsItem *item = mapScene.itemAt(pos);
        if(item)
            mapScene.removeItem(item);
    }
}
