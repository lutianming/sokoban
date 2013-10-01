#include "leveldialog.h"
#include "ui_leveldialog.h"

LevelDialog::LevelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LevelDialog)
{
    ui->setupUi(this);
}

LevelDialog::~LevelDialog()
{
    delete ui;
}

QListView* LevelDialog::getListview()
{
    return ui->listView;
}
QString LevelDialog::getlevel()
{
    QListView *view = ui->listView;
    QModelIndex index = view->currentIndex();
    return view->model()->data(index).toString();
}

