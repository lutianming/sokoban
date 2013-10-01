#include <QtGui/QApplication>
#include "sokobanwindow.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(sokobanResource);

    QApplication a(argc, argv);
    SokonbanWindow w;
    w.setWindowTitle("Sokoban");
    w.setWindowIcon(QIcon(":/images/outbox.jpg"));
    w.show();
    a.setQuitOnLastWindowClosed(true);
    return a.exec();
}
