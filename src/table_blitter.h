#ifndef TABLE_BLITTER_H_INCLUDED
#define TABLE_BLITTER_H_INCLUDED

#include "SDL.h"
#include "SDL_image.h"
#include "card.h"
#include "card_blitter.h"

#define X_START	50
#define Y_START 50
#define SPACING	10

class TableBlitter : private CardBlitter{

public:

	TableBlitter(SDL_Surface *screen, SDL_Surface *card_sprite, SDL_Rect *card_size)
	: CardBlitter(screen, card_sprite, card_size){
	}

	void DrawTable(Card *current_card, Table *table){

		uint8_t suit, row;
		SDL_Rect pos, *c_size;

        c_size = GetCardSize();

		pos.x = X_START + 5 * (c_size->x + SPACING);
		pos.y = Y_START + c_size->y + SPACING;

		// Draw current card, if it has value
		if(current_card->suit != Card::no_suit){
			DrawCard(&pos, current_card);
		}

		// Draw rest of the cards
		for(suit=1; suit<=4; suit++){

			for(row=0; row<ROWS; row++){

				Card t_card;

                t_card.suit = (Card::e_suit)suit;

				switch(suit){

					case (unsigned int)Card::Spade:
						t_card.rank = table->spade[row];
						break;
					case (unsigned int)Card::Heart:
						t_card.rank = table->heart[row];
						break;
					case (unsigned int)Card::Diamond:
						t_card.rank = table->diamond[row];
						break;
					case (unsigned int)Card::Club:
						t_card.rank = table->club[row];
						break;
				};

				// If card has value, print it to
				// selected location.
				if(t_card.suit != Card::no_suit){

					pos.x = X_START + (suit - 1) * (c_size->x + SPACING);
					pos.y = Y_START + row * (c_size->y + SPACING);

					DrawCard(&pos, &t_card);
				}
			}
		}
	}
};

#endif
