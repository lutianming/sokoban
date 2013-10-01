#include "sokobanwindow.h"
#include "ui_sokobanwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QHBoxLayout>
#include "movestepcommand.h"
SokonbanWindow::SokonbanWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::SokonbanWindow),currentState(NORMAL),stack(new QUndoStack())
{
    ui->setupUi(this);
    border = new QWidget( this );
    border->setFixedSize(880,600);
    setCentralWidget( border );
    QHBoxLayout *boxlayout = new QHBoxLayout();
    border->setLayout(boxlayout);
    view = new SokobanView(border);
    infoWidget = new InfoWidget(border);
    infoWidget->setFixedSize(80,600);
    editorWidget = new EditorWidget();
    editorWidget->setFixedSize(80,600);
    boxlayout->addWidget(view);
    boxlayout->addWidget(infoWidget);
    builder = new MapBuilder(view);

    levelDialog = 0;
    connect(view,SIGNAL(win()),this,SLOT(winSlot()));
    connect(editorWidget,SIGNAL(resetSignal()),this,SLOT(mapEditor()));
    connect(editorWidget,SIGNAL(saveSignal()),this,SLOT(saveMap()));
    connect(infoWidget,SIGNAL(restart()),this,SLOT(newGameSlot()));
    connect(infoWidget,SIGNAL(undo()),this,SLOT(undo()));
}

SokonbanWindow::~SokonbanWindow()
{
    delete ui;
    delete border;
}

void SokonbanWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat() || view->isEditting())
    {
        event->ignore();
        return;
    }

     MoveStepCommand *cmd;
    switch(event->key()){
    case Qt::Key_W:         //up
//        doMove = view->moveStep(0,-1);
        cmd = new MoveStepCommand(view,0,-1);
        break;
    case Qt::Key_S:         //down
//        doMove = view->moveStep(0,1);
        cmd = new MoveStepCommand(view,0,1);
        break;
    case Qt::Key_D:         //right
//        doMove = view->moveStep(1,0);
        cmd = new MoveStepCommand(view,1,0);
        break;
    case Qt::Key_A:         //left
//        doMove = view->moveStep(-1,0);
        cmd = new MoveStepCommand(view,-1,0);
        break;
    default:
        event->ignore();
        return;
    }
    if(cmd->doMove()){
        infoWidget->setStep(view->steps());
        stack->push(cmd);
        view->checkWin();
    }else{
        delete cmd;
    }
    event->accept();
}

void SokonbanWindow::newGameSlot()
{
    newGame(1);
}
void SokonbanWindow::chooseLevel()
{
    if(!levelDialog){
        levelDialog = new LevelDialog(this);
        levelDialog->setWindowTitle("levelDialog");

    }
    builder->listMaps(levelDialog->getListview());
    if(levelDialog->exec()){
        newGame(levelDialog->getlevel().toInt());
    }
}
void SokonbanWindow::aboutAuthor()
{
    QMessageBox::about(this,"About author","Tianming Lu\nNJU software institute\n e-mail:lutianming1005@gmail.com");
}

void SokonbanWindow::aboutSokoban()
{
    QMessageBox::about(this,"About sokoban",tr("Sokoban version 1.0\nSokoban is a type of transport puzzle, in which the player pushes boxes around a maze, viewed from above, and tries to put them in predetermined areas. Only one box may be pushed at a time, and boxes cannot be pulled."));
}

void SokonbanWindow::newGame(int level)
{
    changeState(NORMAL);
    infoWidget->setLevel(level);
    infoWidget->setStep(0);
    view->resetInfo(level);
    builder->build(level);
    stack->clear();
}

void SokonbanWindow::winSlot()
{
    QMessageBox::about(this,"congratulation","you win,go to next level!");
    newGame((view->currentLevel())%(builder->getMapNum())+1);

}
void SokonbanWindow::mapEditor()
{
   view->resetInfo(0);
   view->setChanged(false);
   changeState(EDIT);

}
void SokonbanWindow::changeState(int state)
{
    if(currentState == state)
        return;
    currentState = state;
    switch(state){
    case NORMAL:
        view->setEditting(false);
        qDebug() << view->isEditting();
        editorWidget->setParent(0);
        border->layout()->removeWidget(editorWidget);
        infoWidget->setParent(border);
        border->layout()->addWidget(infoWidget);
        break;
    case EDIT:
        view->setEditting(true);
        infoWidget->setParent(0);
        border->layout()->removeWidget(infoWidget);
        editorWidget->setParent(border);
        border->layout()->addWidget(editorWidget);
        break;
    }
}
void SokonbanWindow::saveMap()
{
    builder->saveMap("map.xml",builder->getMapNum()+1);
}
void SokonbanWindow::undo()
{
        stack->undo();
        infoWidget->setStep(view->steps());
}
