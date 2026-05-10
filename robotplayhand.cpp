#include "robotplayhand.h"
#include <QDebug>

RobotPlayHand::RobotPlayHand(Player* player, QObject *parent) : QThread(parent)
{
    m_player = player;
}

void RobotPlayHand::run()
{
    sleep(1);
    m_player->thinkPlayHand();
}
