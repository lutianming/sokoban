#ifndef ITEMLIST_H
#define ITEMLIST_H

#include <QListWidget>

class ItemList : public QListWidget
{
    Q_OBJECT
public:
    explicit ItemList(QWidget *parent = 0);
    void addMapItem(QPixmap pixmap, const QString &name);
protected:
    void startDrag(Qt::DropActions supportedActions);
signals:

public slots:

};

#endif // ITEMLIST_H
