#include "card.h"

Card::Card()
{

}

Card::Card(CardPoint point, CardSuit suit)
{
    setPoint(point);
    setSuit(suit);
}

void Card::setPoint(CardPoint point)
{
    m_point = point;
}

void Card::setSuit(CardSuit suit)
{
    m_suit = suit;
}

char Card::realpoint() const
{
    if (point() < Card_10)
        return char(point() + 50);
    if (point() == Card_10)
        return 'T';
    if (point() == Card_J)
        return 'J';
    if (point() == Card_Q)
        return 'Q';
    if (point() == Card_K)
        return 'K';
    if (point() == Card_A)
        return 'A';
    if (point() == Card_2)
        return '2';
    if (point() == Card_SJ)
        return 'X';
    if (point() == Card_BJ)
        return 'D';
    return ' ';
}

Card::CardPoint Card::point() const
{
    return m_point;
}

Card::CardSuit Card::suit() const
{
    return m_suit;
}

bool lessSort(const Card &c1, const Card &c2)
{
    if(c1.point() == c2.point())
    {
        return c1.suit() < c2.suit();
    }
    else
    {
        return c1.point() < c2.point();
    }
}

bool greaterSort(const Card &c1, const Card &c2)
{
    if(c1.point() == c2.point())
    {
        return c1.suit() > c2.suit();
    }
    else
    {
        return c1.point() > c2.point();
    }
}

bool operator ==(const Card& left, const Card& right)
{
    return (left.point() == right.point() && left.suit() == right.suit());
}

uint qHash(const Card &card)
{
    return card.point() * 100 + card.suit();
}

bool operator <(const Card& c1, const Card& c2)
{
    return lessSort(c1, c2);
}

Card::CardPoint Card::realpoint2point(QChar realpoint)
{
    if ('3' <= realpoint && realpoint <= '9')
        return Card::CardPoint(realpoint.unicode() - 50);
    if (realpoint == 'T')
        return Card::Card_10;
    if (realpoint == 'J')
        return Card::Card_J;
    if (realpoint == 'Q')
        return Card::Card_Q;
    if (realpoint == 'K')
        return Card::Card_K;
    if (realpoint == 'A')
        return Card::Card_A;
    if (realpoint == '2')
        return Card::Card_2;
    if (realpoint == 'X')
        return Card::Card_SJ;
    if (realpoint == 'D')
        return Card::Card_BJ;
    return Card::Card_Begin;
}
