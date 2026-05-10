#include "gamecontrol.h"
#include "playhand.h"
#include <QRandomGenerator>
#include <QTimer>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QHttpMultiPart>
#include <QRandomGenerator>
#include <QFile>
#include <QEventLoop>

GameControl::GameControl(QObject *parent) : QObject(parent)
{

}

void GameControl::playerInit()
{
    // 对象实例化
    m_robotLeft = new Robot("机器人A", this);
    m_robotRight = new Robot("机器人B", this);
    m_user = new UserPlayer("我自己", this);

    // 出牌顺序
    // user
    m_user->setPrevPlayer(m_robotLeft);
    m_user->setNextPlayer(m_robotRight);

    // left robot
    m_robotLeft->setPrevPlayer(m_robotRight);
    m_robotLeft->setNextPlayer(m_user);

    // right robot
    m_robotRight->setPrevPlayer(m_user);
    m_robotRight->setNextPlayer(m_robotLeft);

    // 指定当前玩家
    m_currPlayer = m_user;

    // 处理玩家发射出的信号
    connect(m_user, &UserPlayer::notifyGrabLordBet, this, &GameControl::onGrabBet);
    connect(m_robotLeft, &UserPlayer::notifyGrabLordBet, this, &GameControl::onGrabBet);
    connect(m_robotRight, &UserPlayer::notifyGrabLordBet, this, &GameControl::onGrabBet);

    // 传递出牌玩家对象和玩家打出的牌
    connect(this, &GameControl::pendingInfo, m_robotLeft, &Robot::storePendingInfo);
    connect(this, &GameControl::pendingInfo, m_robotRight, &Robot::storePendingInfo);
    connect(this, &GameControl::pendingInfo, m_user, &Robot::storePendingInfo);

    // 处理玩家出牌
    connect(m_robotLeft, &Robot::notifyPlayHand, this, &GameControl::onPlayHand);
    connect(m_robotRight, &Robot::notifyPlayHand, this, &GameControl::onPlayHand);
    connect(m_user, &Robot::notifyPlayHand, this, &GameControl::onPlayHand);
}


Robot *GameControl::getLeftRobot()
{
    return m_robotLeft;
}

Robot *GameControl::getRightRobot()
{
    return m_robotRight;
}

UserPlayer *GameControl::getUserPlayer()
{
    return m_user;
}

void GameControl::setCurrentPlayer(Player *player)
{
    m_currPlayer = player;
}

Player *GameControl::getCurrentPlayer()
{
    return m_currPlayer;
}

Player *GameControl::getPendPlayer()
{
    return m_pendPlayer;
}

Cards GameControl::getPendCards()
{
    return m_pendCards;
}

void GameControl::initAllCards()
{
    m_allCards.clear();
    for(int p = Card::Card_Begin+1; p<Card::Card_SJ; ++p)
    {
        for(int s = Card::Suit_Begin+1; s<Card::Suit_End; ++s)
        {
            Card c((Card::CardPoint)p, (Card::CardSuit)s);
            m_allCards.add(c);
        }
    }
    m_allCards.add(Card(Card::Card_SJ, Card::Suit_Begin));
    m_allCards.add(Card(Card::Card_BJ, Card::Suit_Begin));
}

Card GameControl::takeOneCard()
{
    return m_allCards.takeRandomCard();
}

Cards GameControl::getSurplusCards()
{
    return m_allCards;
}

void GameControl::resetCardData()
{
    // 洗牌
    initAllCards();
    // 清空所有玩家的牌
    m_robotLeft->clearCards();
    m_robotRight->clearCards();
    m_user->clearCards();
    // 初始化出牌玩家和牌
    m_pendPlayer = nullptr;
    m_pendCards.clear();
}

void GameControl::startLordCard()
{
    QJsonObject jsonData;
    jsonData["action"] = "init";
    QJsonObject dataObj;
    dataObj["three_landlord_cards"] = m_allCards.toCardString();
    int cur_pid = QRandomGenerator::global()->bounded(100000000);
    dataObj["pid"] = cur_pid;
    dataObj["ai_amount"] = 2;

    QJsonObject player1;
    player1["model"] = "WP";
    player1["hand_cards"] = m_robotRight->getCards().toCardString();
    player1["position_code"] = 2;

    QJsonObject player2;
    player2["model"] = "WP";
    player2["hand_cards"] = m_robotLeft->getCards().toCardString();
    player2["position_code"] = 0;

    QJsonArray playerDataArray;
    playerDataArray.append(player1);
    playerDataArray.append(player2);

    dataObj["player_data"] = playerDataArray;
    jsonData["data"] = dataObj;

    QJsonObject playjsonData;
    playjsonData["action"] = "play";
    QJsonObject playdataObj;
    playdataObj["pid"] = cur_pid;
    playdataObj["player"] = 1;
    playdataObj["cards"] = "3";
    playjsonData["data"] = playdataObj;

    sendPOSTRequest(jsonData);
    sendPOSTRequest(playjsonData);

    m_currPlayer->prepareCallLord();
    emit playerStatusChanged(m_currPlayer, ThinkingForCallLord);
}

void GameControl::becomeLord(Player *player, int bet)
{
    m_curBet = bet;
    player->setRole(Player::Lord);
    player->getPrevPlayer()->setRole(Player::Farmer);
    player->getNextPlayer()->setRole(Player::Farmer);

    QJsonObject jsonData;
    jsonData["action"] = "init";
    QJsonObject dataObj;
    dataObj["three_landlord_cards"] = m_allCards.toCardString();
    m_pid = QRandomGenerator::global()->bounded(100000000);
    dataObj["pid"] = m_pid;
    dataObj["ai_amount"] = 2;

    m_currPlayer = player;
    player->storeDispatchCard(m_allCards);

    QJsonObject player1;
    player1["model"] = "WP";
    player1["hand_cards"] = m_robotRight->getCards().toCardString();

    QJsonObject player2;
    player2["model"] = "WP";
    player2["hand_cards"] = m_robotLeft->getCards().toCardString();

    if (m_user == player) {
        player1["position_code"] = 2;
        player2["position_code"] = 0;
    }
    if (m_robotRight == player) {
        player1["position_code"] = 1;
        player2["position_code"] = 2;
    }
    if (m_robotLeft == player) {
        player1["position_code"] = 0;
        player2["position_code"] = 1;
    }

    QJsonArray playerDataArray;
    playerDataArray.append(player1);
    playerDataArray.append(player2);

    dataObj["player_data"] = playerDataArray;
    jsonData["data"] = dataObj;

    sendPOSTRequest(jsonData);

    emit showLordBet(bet);

    QTimer::singleShot(1000, this, [=]()
    {
        emit gameStatusChanged(PlayingHand);
        emit playerStatusChanged(player, ThinkingForPlayHand);
        m_currPlayer->preparePlayHand();
    });
}

void GameControl::clearPlayerScore()
{
    m_robotLeft->setScore(0);
    m_robotRight->setScore(0);
    m_user->setScore(0);
}

int GameControl::getPlayerMaxBet()
{
    return m_betRecord.bet;
}

void GameControl::onGrabBet(Player *player, int bet)
{
    // 1. 通知主界面玩家叫地主了(更新信息提示)
    if(bet == 0 || m_betRecord.bet >= bet)
    {
        emit notifyGrabLordBet(player, 0, false);
    }
    else if(bet > 0 && m_betRecord.bet == 0)
    {
        // 第一个抢地主的玩家
        emit notifyGrabLordBet(player, bet, true);
    }
    else
    {
        // 第2,3个抢地主的玩家
        emit notifyGrabLordBet(player, bet, false);
    }

    qDebug() << "curent player name: " << player->getName() << ", 下注分数: "
            << bet<< ", m_betRecord.times: " << m_betRecord.times;


    // 2. 判断玩家下注是不是3分, 如果是抢地主结束
    if(bet == 3)
    {
        // 玩家成为地主
        becomeLord(player, bet);
        // 清空数据
        m_betRecord.reset();
        return;
    }
    // 3. 下注不够3分, 对玩家的分数进行比较, 分数高的是地主
    if(m_betRecord.bet < bet)
    {
        m_betRecord.bet = bet;
        m_betRecord.player = player;
    }
    m_betRecord.times ++;
    // 如果每个玩家都抢过一次地主, 抢地主结束
    if(m_betRecord.times == 3)
    {
        if(m_betRecord.bet == 0)
        {
            emit gameStatusChanged(DispatchCard);
        }
        else
        {
            becomeLord(m_betRecord.player, m_betRecord.bet);
        }
        m_betRecord.reset();
        return;
    }
    // 4. 切换玩家, 通知下一个玩家继续抢地主
    m_currPlayer = player->getNextPlayer();
    // 发送信号给主界面, 告知当前状态为抢地主
    emit playerStatusChanged(m_currPlayer, ThinkingForCallLord);
    m_currPlayer->prepareCallLord();
}

void GameControl::onPlayHand(Player *player, Cards &card)
{
    // 1. 将玩家出牌的信号转发给主界面和远端AI
    emit notifyPlayHand(player, card);

    if (m_user == player)
    {
        QJsonObject jsonData;
        jsonData["action"] = "play";
        QJsonObject dataObj;
        dataObj["pid"] = m_pid;
        if (m_user->getNextPlayer()->getRole() == Player::Lord)
        {
            dataObj["player"] = 0;
        }
        if (m_user->getRole() == Player::Lord)
        {
            dataObj["player"] = 1;
        }
        if (m_user->getPrevPlayer()->getRole() == Player::Lord)
        {
            dataObj["player"] = 2;
        }
        dataObj["cards"] = card.toCardString();
        jsonData["data"] = dataObj;
        sendPOSTRequest(jsonData);
    }
    // 2. 如果不是空牌, 给其他玩家发送信号, 保存出牌玩家对象和打出的牌
    if(!card.isEmpty())
    {
        m_pendCards = card;
        m_pendPlayer = player;
        emit pendingInfo(player, card);
    }
    // 如果有炸弹, 低分翻倍
    PlayHand::HandType type = PlayHand(card).getHandType();
    if(type == PlayHand::Hand_Bomb || type == PlayHand::Hand_Bomb_Jokers)
    {
        m_curBet = m_curBet * 2;
    }

    // 3. 如果玩家的牌出完了, 计算本局游戏的总分
    if(player->getCards().isEmpty())
    {
        Player* prev = player->getPrevPlayer();
        Player* next = player->getNextPlayer();
        if(player->getRole() == Player::Lord)
        {
            player->setScore(player->getScore() + 2 * m_curBet);
            prev->setScore(prev->getScore() - m_curBet);
            next->setScore(next->getScore() - m_curBet);
            player->setWin(true);
            prev->setWin(false);
            next->setWin(false);
        }
        else
        {
            player->setWin(true);
            player->setScore(player->getScore() + m_curBet);
            if(prev->getRole() == Player::Lord)
            {
                prev->setScore(prev->getScore() - 2 * m_curBet);
                next->setScore(next->getScore() + m_curBet);
                prev->setWin(false);
                next->setWin(true);
            }
            else
            {
                next->setScore(next->getScore() - 2 * m_curBet);
                prev->setScore(prev->getScore() + m_curBet);
                next->setWin(false);
                prev->setWin(true);
            }
        }
        emit playerStatusChanged(player, GameControl::Winning);
        return;
    }
    // 4. 牌没有出完, 下一个玩家继续出牌
    m_currPlayer = player->getNextPlayer();
    m_currPlayer->preparePlayHand();
    emit playerStatusChanged(m_currPlayer, GameControl::ThinkingForPlayHand);
}

void GameControl::sendPOSTRequest(QJsonObject params)
{
    qDebug() << "Send: " << params;

    // 创建事件循环
    QEventLoop loop;

    QNetworkAccessManager* nam = new QNetworkAccessManager(this);

    QNetworkRequest request;
    request.setUrl(QUrl("http://47.115.62.20:3002"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonDocument jsonDoc(params);
    QByteArray jsonData = jsonDoc.toJson();

    connect(nam, &QNetworkAccessManager::finished, this, [&](QNetworkReply* reply) {
        if(reply->error())
        {
            qDebug() << "ERROR!";
            qDebug() << reply->errorString();
        }
        else
        {
            QString answer = QString::fromUtf8(reply->readAll());
            QJsonParseError jsonError;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(answer.toUtf8(), &jsonError);
            if(jsonError.error != QJsonParseError::NoError)
            {
                qDebug() << "JSON Parse error!";
            }
            else
            {
                QString filename = "output.json";
                QFile file(filename);
                if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
                    file.close();
                }
                if(!file.open(QIODevice::ReadWrite))
                {
                    qDebug() << "Error opening file for writing: " << filename;
                    return;
                }
                qDebug() << "Reply: " << jsonDoc;
                file.write(jsonDoc.toJson(QJsonDocument::Indented));
                file.close();
            }
        }

        reply->deleteLater();

        // 在请求完成时退出事件循环
        loop.quit();
    });

    nam->post(request, jsonData);

    // 开始事件循环，直到请求完成
    loop.exec();
}
