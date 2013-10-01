#include "infowidget.h"
#include "ui_infowidget.h"

InfoWidget::InfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoWidget)
{
    ui->setupUi(this);
    connect(ui->restartButton,SIGNAL(clicked()),this,SIGNAL(restart()));
    connect(ui->undoButton,SIGNAL(clicked()),this,SIGNAL(undo()));
}

InfoWidget::~InfoWidget()
{
    delete ui;
}

void InfoWidget::setLevel(int i)
{
    ui->levelLcdNumber->display(i);
}

void InfoWidget::setStep(int i)
{
    ui->stepLcdNumber->display(i);
}
