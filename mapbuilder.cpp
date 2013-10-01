#include "mapbuilder.h"
#include "sprites.h"
#include <QXmlStreamWriter>
#include <QStringListModel>
#include <QDebug>
#include <QFile>
#include <QMessageBox>

MapBuilder::MapBuilder(SokobanView *view):mapNum(0)
{
    this->view = view;
    readPixmaps();
    initMaps("map.xml");
}
MapBuilder::~MapBuilder()
{
    delete maps;
}

bool MapBuilder::build(int level)
{
    QDomElement root = maps->documentElement();
    if(root.tagName() != "sokoban"){
        qDebug() << "This is not a sokoban map file";
        return false;
    }
    QDomNode node = root.firstChild();
    while(!node.isNull()){
        if(node.toElement().attribute("level").toInt() == level){
            parseMap(node.toElement());
            return true;
        }
        node = node.nextSibling();
    }
    return false;
}

void MapBuilder::parseMap(const QDomElement &element){
    QDomNode node = element.firstChild();
    while(!node.isNull()){
        QString tag = node.toElement().tagName();
        QPoint pos = getPos(node.toElement());
        if(tag == "wall")
            buildWall(pos);
        else if(tag == "box")
            buildBox(pos);
        else if(tag == "destination")
            buildDes(pos);
        else if(tag == "boxman")
            buildBoxman(pos);
        else if(tag == "floor")
            buildFloor(pos);
        node = node.nextSibling();
    }

}

QPoint MapBuilder::getPos(const QDomElement &element)
{
    int row = 0;
    int column = 0;
    row = element.attribute("row").toInt();
    column = element.attribute("column").toInt();
    return QPoint(row * Item::WIDTH,column * Item::HEIGHT);
}

bool MapBuilder::saveMap(const QString &filename, int level)
{
    if(!view->isChanged()){
        QMessageBox::warning(view,"warning","you have not change anything!");
        return false;
    }
    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(0,"Error","Error: Cannot write file");
        //            qDebug() << "Error: Cannot write file "
        //                      << qPrintable(filename) << ": "
        //                     << qPrintable(file.errorString());
        return false;
    }

    QTextStream out(&file);
    QDomElement map = maps->createElement("map");
    map.setAttribute("level",level);
    QList<QGraphicsItem*> items = view->map().items();
    foreach(QGraphicsItem *item,items){
        QDomElement mapItem;
        if(item->data(0) == "wall")
            mapItem = maps->createElement("wall");
        else if(item->data(0) == "box")
            mapItem = maps->createElement("box");
        else if(item->data(0) == "destination")
            mapItem = maps->createElement("destination");
        else if(item->data(0) == "boxman")
            mapItem = maps->createElement("boxman");
        else if(item->data(0) == "floor")
            mapItem = maps->createElement("floor");
        mapItem.setAttribute("row",(int)item->x() / Item::WIDTH);
        mapItem.setAttribute("column",(int)item->y() / Item::HEIGHT);
        map.appendChild(mapItem);
    }
    maps->documentElement().appendChild(map);
    maps->save(out,4);
    file.close();
    if (file.error()) {
        QMessageBox::warning(0,"Error","Error: Cannot write file");
        //            qDebug() << "Error: Cannot write file "
        //                     << qPrintable(filename) << ": "
        //                     << qPrintable(file.errorString());
        return false;
    }
    QMessageBox::about(view,"done","map saved!");
    return true;

}

bool MapBuilder::listMaps(QListView *view)
{

    QDomElement root = maps->documentElement();
    if(root.tagName() != "sokoban"){
        QMessageBox::warning(0,"Error","Error: This is not a sokoban map file");
        return false;
    }
    QDomNode node = root.firstChild();
    list.clear();
    while(!node.isNull()){
        list.push_back(node.toElement().attribute("level"));
        node = node.nextSibling();
    }
    view->setModel(new QStringListModel(list));
    return false;
}
bool MapBuilder::initMaps(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(0,"Error","Error: Cannot read file");
        //            qDebug() << "Error: Cannot read file " << qPrintable(filename)
        //                    << ": " << qPrintable(file.errorString());
        return false;
    }

    QString errorStr;
    int errorLine;
    int errorColumn;
    QDomDocument *doc = new QDomDocument();
    if (!doc->setContent(&file, false, &errorStr, &errorLine,
                         &errorColumn)) {
        QMessageBox::warning(0,"Error","Error: unable to parse the map file");
        return false;
    }
    mapNum = doc->documentElement().childNodes().length();
    maps = doc;
    return true;
}

bool MapBuilder::readPixmaps()
{
        pixmaps.push_back(QPixmap(":/images/outbox.jpg"));
        pixmaps.push_back(QPixmap(":/images/inbox.jpg"));
        pixmaps.push_back(QPixmap(":/images/man.jpg"));
        pixmaps.push_back(QPixmap(":/images/wall.jpg"));
        pixmaps.push_back(QPixmap(":/images/destination.jpg"));
        pixmaps.push_back(QPixmap(":/images/floor.jpg"));
    return true;
}

void MapBuilder::buildBox(QPoint &pos)
{
    Box *box = new Box(pixmaps[0],pixmaps[1]);
    box->setPos(pos);
    view->map().addItem(box);
}
void MapBuilder::buildBoxman(QPoint &pos)
{
    BoxMan *man = new BoxMan(pixmaps[2]);
    man->setPos(pos);
    view->map().addItem(man);
    view->setBoxman(man);
}
void MapBuilder::buildDes(QPoint &pos)
{
    Destination *des = new Destination(pixmaps[4]);
    des->setPos(pos);
    view->map().addItem(des);
    view->desCountPlus();;
}
void MapBuilder::buildWall(QPoint &pos)
{
    Wall *wall = new Wall(pixmaps[3]);
    wall->setPos(pos);
    view->map().addItem(wall);
}
void MapBuilder::buildFloor(QPoint &pos)
{
    Floor *floor = new Floor(pixmaps[5]);
    floor->setPos(pos);
    view->map().addItem(floor);
}
