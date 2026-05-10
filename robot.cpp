#include "robot.h"
#include "robotgraplord.h"
#include "robotplayhand.h"
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QRandomGenerator>

Robot::Robot(QObject *parent) : Player(parent)
{
    m_type = Player::Robot;
}

void Robot::prepareCallLord()
{
    RobotGrapLord* subThread = new RobotGrapLord(this);
    connect(subThread, &RobotGrapLord::finished, this, [=](){
        qDebug() << "RobotGrapLord, Robot name: " << this->getName();
        subThread->deleteLater();
    });
    subThread->start();
}

void Robot::preparePlayHand()
{
    RobotPlayHand* subThread = new RobotPlayHand(this);
    connect(subThread, &RobotGrapLord::finished, this, [=](){
        qDebug() << "RobotPlayHand, Robot name: " << this->getName();
        subThread->deleteLater();
    });

    subThread->start();
}

void Robot::thinkCallLord()
{
    int weight = 0;

    QString filename = "output.json";
    QFile file(filename);
    if(!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Error opening file for reading: " << filename;
        return;
    }
    QByteArray jsonData = file.readAll();
    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    QJsonObject data = (document.object())["data"].toObject();
    QJsonArray play = data["play"].toArray();
    QJsonObject playItem;
    if (getPrevPlayer()->getName() == "我自己")
    {
        playItem = play[0].toObject();
    }
    else
    {
        playItem = play[1].toObject();
    }
    double winProbability = playItem["confidence"].toDouble();

    qDebug() << "winProbability:" <<  winProbability;

    if (winProbability >= 55)
    {
        weight = 1;
    }
    if (winProbability >= 70)
    {
        weight = 2;
    }
    if (winProbability >= 85)
    {
        weight = 3;
    }

    grabLordBet(weight);
}

void Robot::thinkPlayHand()
{
    QString filename = "output.json";
    QFile file(filename);
    if(!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Error opening file for reading: " << filename;
        return;
    }
    QByteArray jsonData = file.readAll();
    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    QJsonObject data = (document.object())["data"].toObject();
    QJsonArray play = data["play"].toArray();
    QJsonObject playItem;
    if (getPrevPlayer()->getName() == "我自己")
    {
        playItem = play[0].toObject();
    }
    else
    {
        if (play[1].toObject()["cards"].isNull())
        {
            playItem = play[0].toObject();
        }
        else
        {
            playItem = play[1].toObject();
        }
    }
    QJsonArray arraycards = playItem["cards"].toArray();
    QString cards;
    for (int i = 0; i < arraycards.size(); i ++)
    {
        cards += arraycards[i].toString();
    }
    qDebug() << "Cards:" << cards;
    Cards cs = m_cards.selectValidCards(cards);
    file.close();
    playHand(cs);
}
