#ifndef SOKOBANVIEW_H
#define SOKOBANVIEW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "sprites.h"
class SokobanView : public QWidget
{
    Q_OBJECT
public:
    friend class MoveStepCommand;
    explicit SokobanView(QWidget *parent = 0);
    void resetInfo(int level=1);
    int currentLevel(){return level;}
    int steps(){return stepCount;}
    QGraphicsScene& map(){return mapScene;}
    void desCountPlus(){ desCount++;}
    void setBoxman(BoxMan* boxman){this->boxman = boxman;}
    void checkWin();
    bool isEditting(){return editting;}
    void setEditting(bool edit){editting = edit;}
    bool isChanged(){return changed;}
    void setChanged(bool changed){this->changed = changed;}
protected:
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void mousePressEvent(QMouseEvent *event);
signals:
    void win();
private:
    QGraphicsScene mapScene;
    QGraphicsView view;
    BoxMan *boxman;
    bool editting;
    bool changed;
    int level;
    int stepCount;
    int desCount;
    int inPlaceCount;
    void boxIn(QGraphicsItem *box);
    void boxOut(QGraphicsItem *box);
signals:

public slots:

};

#endif // SOKOBANVIEW_H
