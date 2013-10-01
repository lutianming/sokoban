#ifndef SOKOBANWINDOW_H
#define SOKOBANWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QUndoStack>
#include "sokobanview.h"
#include "leveldialog.h"
#include "infowidget.h"
#include "mapbuilder.h"
#include "editorwidget.h"
namespace Ui {
    class SokonbanWindow;
}

class SokonbanWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SokonbanWindow(QWidget *parent = 0);
    ~SokonbanWindow();
    enum{ NORMAL,EDIT };
protected:
    virtual void keyPressEvent(QKeyEvent *);

public slots:
    void newGameSlot();
    void chooseLevel();
    void aboutSokoban();
    void aboutAuthor();
    void winSlot();
    void newGame(int level);
    void mapEditor();
    void saveMap();
    void undo();
private:
    Ui::SokonbanWindow *ui;
    int currentState;
    QUndoStack *stack;
    QWidget *border;
    SokobanView *view;
    InfoWidget *infoWidget;
    EditorWidget *editorWidget;
    LevelDialog *levelDialog;
    MapBuilder *builder;
    void changeState(int state);
};

#endif // SOKONBANWINDOW_H
