#include "gamepanel.h"

#include <QApplication>
#include <QResource>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<Cards>("Cards&");
    qRegisterMetaType<Cards>("Cards");
    GamePanel* panel = new GamePanel;
    panel->show();
    return a.exec();
}
