#ifndef LEVELDIALOG_H
#define LEVELDIALOG_H

#include <QDialog>
#include <QListView>
namespace Ui {
    class LevelDialog;
}

class LevelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LevelDialog(QWidget *parent = 0);
    QListView* getListview();
    QString getlevel();
    ~LevelDialog();
private:
    Ui::LevelDialog *ui;
};

#endif // LEVELDIALOG_H
