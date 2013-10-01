#include "editorwidget.h"
#include "ui_editorwidget.h"

EditorWidget::EditorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorWidget)
{
    ui->setupUi(this);
    itemList = new ItemList(this);
    itemList->setFixedSize(80,350);
    connect(ui->resetButton,SIGNAL(clicked()),this,SIGNAL(resetSignal()));
    connect(ui->saveButton,SIGNAL(clicked()),this,SIGNAL(saveSignal()));
}

EditorWidget::~EditorWidget()
{
    delete ui;
}
