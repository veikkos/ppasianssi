#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

class Card{

public:
    typedef enum{
        no_suit = 0,
        Club = 1,
        Spade = 2,
        Heart = 3,
        Diamond = 4
    }e_suit;

    typedef enum{
        no_rank = 0,
        Ace = 1,
        Two = 2,
        Three = 3,
        Four = 4,
        Five = 5,
        Six = 6,
        Seven = 7,
        Eight = 8,
        Nine = 9,
        Ten = 10,
        Jack = 11,
        Queen = 12,
        King = 13
    }e_rank;

    e_suit suit;
    e_rank rank;
};

#endif // CARD_H_INCLUDED
