#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED

#include "card.h"

#define ROWS 3

class Table{

public:
    Table(){

        Clear();
    }

    bool Push(Card* card){

        uint8_t i, *row_ptr;
        Card::e_rank *s_ptr;

        switch(card->suit){

            case Card::Spade:
            {
                row_ptr = &spade_ptr;
                s_ptr = spade;

                break;
            }
            case Card::Heart:
            {
                row_ptr = &heart_ptr;
                s_ptr = heart;

                break;
            }
            case Card::Club:
            {
                row_ptr = &club_ptr;
                s_ptr = club;

                break;
            }
            case Card::Diamond:
            {
                row_ptr = &diamond_ptr;
                s_ptr = diamond;

                break;
            }
            default: return true;
        }

            if(card->rank == Card::Ace){

                *row_ptr = 0;

                for(i=1; i<ROWS; i++){
                    s_ptr[i] = Card::no_rank;
                }

            }else{

                if(!(s_ptr[*row_ptr] < card->rank || \
                     s_ptr[*row_ptr] == Card::King || \
                     s_ptr[*row_ptr] == Card::Ace)){

                    if(*row_ptr + 1 >= ROWS){
                        return false;
                    }else{
                        (*row_ptr)++;
                    }

                    s_ptr[*row_ptr] = card->rank;
                }
            }

              s_ptr[*row_ptr] = card->rank;

        return true;
    }

    void Clear(){

        uint8_t i;

        for(i=0; i<ROWS; i++){
            spade[i] = Card::no_rank;
            diamond[i] = Card::no_rank;
            heart[i] = Card::no_rank;
            club[i] = Card::no_rank;
        }

        spade_ptr = 0;
        diamond_ptr = 0;
        heart_ptr = 0;
        club_ptr = 0;
    }

    Card::e_rank spade[ROWS], diamond[ROWS], heart[ROWS], club[ROWS];
    uint8_t spade_ptr, diamond_ptr, heart_ptr, club_ptr;
};

#endif // TABLE_H_INCLUDED
