#ifndef DECK_H_INCLUDED
#define DECK_H_INCLUDED

#include <stdlib.h>
#include <time.h>
#include "card.h"

#define DECK_SIZE   52

class Deck{

public:

    Deck(){

        srand ((unsigned int)time(NULL));

        Shuffle();
    }

    ~Deck(){

    }

    void Shuffle(){

        uint8_t i, k, s, r;

        d_ptr = 0;

        for(i=0; i<DECK_SIZE + 1; i++){
            deck[i].suit = Card::no_suit;
            deck[i].rank = Card::no_rank;
        }

        for(s=Card::Club; s<=Card::Diamond; s += 1){

            for(r=Card::Ace; r<=Card::King; r++){

                do{
                   k = rand() % DECK_SIZE;
                }while(deck[k].suit != Card::no_suit);

                deck[k].suit = (Card::e_suit)s;
                deck[k].rank = (Card::e_rank)r;
            }
        }
    }

    Card *CurrentCard(){

        return &deck[d_ptr];
    }

    void NextCard(){

        deck[d_ptr].rank = Card::no_rank;
        deck[d_ptr].suit = Card::no_suit;

        if(d_ptr < DECK_SIZE){
            d_ptr++;
        }
    }

    int CardsLeft(){

        return DECK_SIZE - (int)d_ptr;
    }

    void PushBack(){

        Card current;
        uint8_t i;

        current = *CurrentCard();

        for(i=d_ptr; i<DECK_SIZE - 1; i++){
            deck[i] = deck[i+1];
        }

        deck[DECK_SIZE - 1] = current;
    }

private:

    Card deck[DECK_SIZE + 1];

    uint8_t d_ptr;
};

#endif // DECK_H_INCLUDED
