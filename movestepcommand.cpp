#include "movestepcommand.h"
#include <QDebug>
MoveStepCommand::MoveStepCommand(SokobanView *view, int x, int y):QUndoCommand(0)
{
    this->view = view;
    man = view->boxman;
    manX = man->x();
    manY = man->y();
    box = 0;
    moveStep(x,y);
}

void MoveStepCommand::undo()
{
    view->stepCount--;
    man->setPos(manX, manY);
    if(box){
        box->setPos(boxX,boxY);
        if(inBox){
            view->boxIn(box);
        }else{
            view->boxOut(box);
        }
    }
}

bool MoveStepCommand::moveStep(int x, int y)
{
    if(!collision(man,x,y)){
        moveStep(man,x,y);
        view->stepCount++;
        return move = true;
    }
    return move = false;
}

void MoveStepCommand::moveStep(QGraphicsItem *item, int x, int y)
{
    int px = item->x();
    int py = item->y();
    item->setX(px+x*Item::WIDTH);
    item->setY(py+y*Item::HEIGHT);
}

bool MoveStepCommand::collision(QGraphicsItem *item, int x, int y)
{
    int centerX = (int)item->x() + Item::WIDTH/2;
    int centerY = (int)item->y() + Item::HEIGHT/2;
    QGraphicsItem *neighber;
    if(neighber = view->mapScene.itemAt(centerX+x*Item::WIDTH,centerY+y*Item::HEIGHT)){
        if(neighber->data(0) == "wall")
            return true;
        if(neighber->data(0) == "box"){
            box = neighber;
            boxX = box->x();
            boxY = box->y();
            inBox = box->data(1).toBool();
            int centerX = (int)neighber->x() + Item::WIDTH/2;
            int centerY = (int)neighber->y() + Item::HEIGHT/2;
            QGraphicsItem *next;
            if(next = view->mapScene.itemAt(centerX+x*Item::WIDTH,centerY+y*Item::HEIGHT)){
                if((next->data(0) == "wall") || (next->data(0) == "box"))
                    return true;
                else{
                    if(next->data(0) == "destination"){
                        view->boxIn(neighber);
                    }else{
                        view->boxOut(neighber);
                    }
                    moveStep(neighber,x,y);
                    return false;
                }
            }else{
                view->boxOut(neighber);
                moveStep(neighber,x,y);
                return false;
            }
        }
    }
    return false;
}
