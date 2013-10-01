#ifndef MAPBUILDER_H
#define MAPBUILDER_H
#include <QDomDocument>
#include <QString>
#include <QListView>
#include <QVector>
#include "sokobanview.h"
class MapBuilder
{
public:
    MapBuilder(SokobanView *view);
    ~MapBuilder();
    bool build(int level=1);
    bool saveMap(const QString &filename,int level);
    bool listMaps(QListView *view);
    bool initMaps(const QString &filename);
    int getMapNum(){return mapNum;}
    void buildWall(QPoint &pos);
    void buildBox(QPoint &pos);
    void buildDes(QPoint &pos);
    void buildBoxman(QPoint &pos);
    void buildFloor(QPoint &pos);
private:
    void parseMap(const QDomElement &element);
    QPoint getPos(const QDomElement &element);
    bool readPixmaps();
    QVector<QPixmap> pixmaps;
    QDomDocument *maps;
    QStringList list;
    SokobanView *view;
    int mapNum;
};

#endif // MAPBUILDER_H
