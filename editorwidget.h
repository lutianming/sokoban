#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <QWidget>
#include "itemlist.h"
namespace Ui {
    class EditorWidget;
}

class EditorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EditorWidget(QWidget *parent = 0);
    ~EditorWidget();
signals:
    void resetSignal();
    void saveSignal();
private:
    Ui::EditorWidget *ui;
    ItemList *itemList;
};

#endif // EDITORWIDGET_H
