#ifndef MOVESTEPCOMMAND_H
#define MOVESTEPCOMMAND_H

#include <QUndoCommand>
#include "sokobanview.h"
#include "sprites.h"
class MoveStepCommand : public QUndoCommand
{
public:
    explicit MoveStepCommand(SokobanView *view,int x,int y);
    virtual void undo();
    bool doMove(){return move;}
private:
    bool moveStep(int x,int y);
    void moveStep(QGraphicsItem *item, int x, int y);
    bool collision(QGraphicsItem *item, int x, int y);
    SokobanView *view;
    BoxMan *man;
    int manX,manY;
    QGraphicsItem *box;
    int boxX,boxY;
    bool inBox;
    bool move;
};

#endif // MOVESTEPCOMMAND_H
