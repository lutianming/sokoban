#include "itemlist.h"
#include "sprites.h"
#include <QMimeData>
#include <QDrag>
#include <QDragMoveEvent>
#include <QDragEnterEvent>
#include <QDebug>
ItemList::ItemList(QWidget *parent) :
        QListWidget(parent)
{
    addMapItem(QPixmap(":/images/destination.jpg"),"destination");
    addMapItem(QPixmap(":/images/floor.jpg"),"floor");
    addMapItem(QPixmap(":/images/man.jpg"),"boxman");
    addMapItem(QPixmap(":/images/wall.jpg"),"wall");
    addMapItem(QPixmap(":/images/outbox.jpg"),"box");
    setDragEnabled(true);
    setViewMode(QListView::IconMode);
    setIconSize(QSize(60, 60));
    setSpacing(10);
}

void ItemList::addMapItem(QPixmap pixmap, const QString &name)
{
    QListWidgetItem *mapItem = new QListWidgetItem(this);
    mapItem->setIcon(QIcon(pixmap));
    mapItem->setData(Qt::UserRole, QVariant(pixmap));
    mapItem->setData(Qt::UserRole+1, name);
    mapItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable
                      | Qt::ItemIsDragEnabled);
}


void ItemList::startDrag(Qt::DropActions /*supportedActions*/)
{
    QListWidgetItem *item = currentItem();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    QPixmap pixmap = qVariantValue<QPixmap>(item->data(Qt::UserRole));
    QString name = item->data(Qt::UserRole+1).toString();

    dataStream << pixmap << name;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("image/x-mapItem", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(QPoint(pixmap.width()/2, pixmap.height()/2));
    drag->setPixmap(pixmap);
    drag->exec(Qt::MoveAction);
}

