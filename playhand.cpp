#include "playhand.h"

PlayHand::PlayHand()
{

}

PlayHand::PlayHand(Cards &cards)
{
    // 1. 对扑克牌进行分类: 1张的, 2张, 3张, 4张有多少种
    classify(cards);
    // 2. 对牌型进行分类
    judgeCardType();
}

PlayHand::PlayHand(HandType type, Card::CardPoint pt, int extra)
{
    m_type = type;
    m_pt = pt;
    m_extra = extra;
}

void PlayHand::classify(Cards &cards)
{
    CardList list = cards.toCardList();
    int cardRecord[Card::Card_End];
    memset(cardRecord, 0, sizeof(int) * Card::Card_End);

    for(int i=0; i<list.size(); ++i)
    {
        Card c = list.at(i);
        cardRecord[c.point()] ++;
    }

    for (int i = 0; i < 4; ++i) m_card[i].clear();

    for(int i=0; i<Card::Card_End; ++i)
    {
        if(cardRecord[i] >= 1 && cardRecord[i] <= 4)
            m_card[cardRecord[i] - 1].push_back((Card::CardPoint)i);
    }
}

void PlayHand::judgeCardType()
{
    m_type = Hand_Unknown;
    m_pt = Card::Card_Begin;
    m_extra = 0;

    if(isPass())
    {
        m_type = Hand_Pass;
    }
    if(isSingle())
    {
        m_type = Hand_Single;
        m_pt = m_card[0][0];
    }
    else if(isPair())
    {
        m_type = Hand_Pair;
        m_pt = m_card[1][0];
    }
    else if(isTriple())
    {
        m_type = Hand_Triple;
        m_pt = m_card[2][0];
    }
    else if(isTripleSingle())
    {
        m_type = Hand_Triple_Single;
        m_pt = m_card[2][0];
    }
    else if(isTriplePair())
    {
        m_type = Hand_Triple_Pair;
        m_pt = m_card[2][0];
    }
    else if(isPlane())
    {
        m_type = Hand_Plane;
        // 记录点数最小的牌
        m_pt = m_card[2][0];
    }
    else if(isPlaneTwoSingle())
    {
        m_type = Hand_Plane_Two_Single;
        // 记录点数最小的牌
        m_pt = m_card[2][0];
    }
    else if(isPlaneTwoPair())
    {
        m_type = Hand_Plane_Two_Pair;
        // 记录点数最小的牌
        m_pt = m_card[2][0];
    }
    else if(isSeqPair())
    {
        m_type = Hand_Seq_Pair;
        // 记录点数最小的牌
        m_pt = m_card[1][0];
        m_extra = m_card[1].size();
    }
    else if(isSeqSingle())
    {
        m_type = Hand_Seq_Single;
        // 记录点数最小的牌
        m_pt = m_card[0][0];
        m_extra = m_card[0].size();
    }
    else if(isBomb())
    {
        m_type = Hand_Bomb;
        // 记录点数最小的牌
        m_pt = m_card[3][0];
    }
    else if(isBombSingle())
    {
        m_type = Hand_Bomb_Single;
        // 记录点数最小的牌
        m_pt = m_card[3][0];
    }
    else if(isBombPair())
    {
        m_type = Hand_Bomb_Pair;
        // 记录点数最小的牌
        m_pt = m_card[3][0];
    }
    else if(isBombTwoSingle())
    {
        m_type = Hand_Bomb_Two_Single;
        // 记录点数最小的牌
        m_pt = m_card[3][0];
    }
    else if(isBombJokers())
    {
        m_type = Hand_Bomb_Jokers;
    }
    else if(isBombJokersSingle())
    {
        m_type = Hand_Bomb_Jokers_Single;
    }
    else if(isBombJokersPair())
    {
        m_type = Hand_Bomb_Jokers_Pair;
    }
    else if(isBombJokersTwoSingle())
    {
        m_type = Hand_Bomb_Jokers_Two_Single;
    }
}

bool PlayHand::isPass()
{
    for (int i = 0; i < 3; ++i) if (m_card[i].size()) return false;
    return true;
}

PlayHand::HandType PlayHand::getHandType()
{
    return m_type;
}

Card::CardPoint PlayHand::getCardPoint()
{
    return m_pt;
}

int PlayHand::getExtra()
{
    return m_extra;
}

bool PlayHand::canBeat(const PlayHand &other)
{
    // 我的牌型是未知的
    if(m_type == Hand_Unknown)
    {
        return false;
    }

    bool flag = false;
    flag |= (other.m_type == Hand_Pass);
    flag |= (m_type == Hand_Bomb_Jokers);
    flag |= (m_type == Hand_Bomb && other.m_type >= Hand_Single && other.m_type <= Hand_Seq_Single);
    flag |= (m_type == other.m_type && m_pt > other.m_pt && (m_extra == other.m_extra || m_type != Hand_Seq_Pair && m_type != Hand_Seq_Single));
    return flag;
}

bool PlayHand::fitPattern(int *pattern) {
    for (int i = 0; i < 4; ++i) if (m_card[i].size() != pattern[i]) return false;
    return true;
}

bool PlayHand::isSingle()
{
    int pattern[4] = {1, 0, 0, 0};
    return fitPattern(pattern);
}

bool PlayHand::isPair()
{
    int pattern[4] = {0, 1, 0, 0};
    return fitPattern(pattern);
}

bool PlayHand::isTriple()
{
    int pattern[4] = {0, 0, 1, 0};
    return fitPattern(pattern);
}

bool PlayHand::isTripleSingle()
{
    int pattern[4] = {1, 0, 1, 0};
    return fitPattern(pattern);
}

bool PlayHand::isTriplePair()
{
    int pattern[4] = {0, 1, 1, 0};
    return fitPattern(pattern);
}

bool PlayHand::isPlane()
{
    int pattern[4] = {0, 0, 2, 0};
    std::sort(m_card[2].begin(), m_card[2].end());
    return fitPattern(pattern) && m_card[2][1] - m_card[2][0] == 1 && m_card[2][1] < Card::Card_2;
}

bool PlayHand::isPlaneTwoSingle()
{
    std::sort(m_card[2].begin(), m_card[2].end());
    std::sort(m_card[0].begin(), m_card[0].end());
    int pattern[4] = {2, 0, 2, 0};
    return fitPattern(pattern) && m_card[2][1] - m_card[2][0] == 1 && m_card[2][1] < Card::Card_2 && m_card[0][0] != Card::Card_SJ && m_card[0][1] != Card::Card_BJ;
}

bool PlayHand::isPlaneTwoPair()
{
    std::sort(m_card[2].begin(), m_card[2].end());
    int pattern[4] = {0, 2, 2, 0};
    return fitPattern(pattern) && m_card[2][1] - m_card[2][0] == 1 && m_card[2][1] < Card::Card_2;
}

bool PlayHand::isSeqPair()
{
    if(m_card[0].isEmpty() && m_card[1].size() >= 3 && m_card[2].isEmpty() && m_card[3].isEmpty())
    {
        std::sort(m_card[1].begin(), m_card[1].end());
        if(m_card[1].last() - m_card[1].first() == (m_card[1].size() -1) &&
            m_card[1].first() >= Card::Card_3 && m_card[1].last() < Card::Card_2)
        {
            return true;
        }
    }
    return false;
}

bool PlayHand::isSeqSingle()
{
    if(m_card[0].size() >= 5 && m_card[1].isEmpty() && m_card[2].isEmpty() && m_card[3].isEmpty())
    {
        std::sort(m_card[0].begin(), m_card[0].end());
        if(m_card[0].last() - m_card[0].first() == (m_card[0].size() -1) &&
            m_card[0].first() >= Card::Card_3 && m_card[0].last() < Card::Card_2)
        {
            return true;
        }
    }
    return false;
}

bool PlayHand::isBomb()
{
    int pattern[4] = {0, 0, 0, 1};
    return fitPattern(pattern);
}

bool PlayHand::isBombSingle()
{
    int pattern[4] = {1, 0, 0, 1};
    return fitPattern(pattern);
}

bool PlayHand::isBombPair()
{
    int pattern[4] = {0, 1, 0, 1};
    return fitPattern(pattern);
}

bool PlayHand::isBombTwoSingle()
{
    int pattern[4] = {2, 0, 0, 1};
    std::sort(m_card[0].begin(), m_card[0].end());
    return fitPattern(pattern) && m_card[0].first() != Card::Card_SJ && m_card[0].last() != Card::Card_BJ;
}

bool PlayHand::isBombJokers()
{
    int pattern[4] = {2, 0, 0, 0};
    std::sort(m_card[0].begin(), m_card[0].end());
    return fitPattern(pattern) && m_card[0].first() == Card::Card_SJ && m_card[0].last() == Card::Card_BJ;
}

bool PlayHand::isBombJokersSingle()
{
    int pattern[4] = {3, 0, 0, 0};
    std::sort(m_card[0].begin(), m_card[0].end());
    return fitPattern(pattern) && m_card[0][1] == Card::Card_SJ && m_card[0][2] == Card::Card_BJ;
}

bool PlayHand::isBombJokersPair()
{
    int pattern[4] = {2, 1, 0, 0};
    std::sort(m_card[0].begin(), m_card[0].end());
    return fitPattern(pattern) && m_card[0][0] == Card::Card_SJ && m_card[0][1] == Card::Card_BJ;
}

bool PlayHand::isBombJokersTwoSingle()
{
    int pattern[4] = {4, 0, 0, 0};
    std::sort(m_card[0].begin(), m_card[0].end());
    return fitPattern(pattern) && m_card[0][2] == Card::Card_SJ && m_card[0][3] == Card::Card_BJ;
}

