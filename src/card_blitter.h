#ifndef CARD_BLITTER_H_INCLUDED
#define CARD_BLITTER_H_INCLUDED

#include "SDL.h"
#include "SDL_image.h"
#include "card.h"

#define CRD_SPX     1
#define CRD_SPYT    1
#define CRD_SPYB    1

class CardBlitter{

public:

	CardBlitter(SDL_Surface *screen, SDL_Surface *card_sprite, SDL_Rect *card_size){

		m_screen = screen;
		m_card_sprite = card_sprite;
		m_card_size = *card_size;
	};

	void DrawCard(SDL_Rect *pos, Card *card){

		SDL_Rect clip;

        if(card->rank != Card::no_rank && card->suit != Card::no_suit){

            clip.x = CRD_SPX + (card->rank - 1) * m_card_size.x;
            clip.y = CRD_SPYT + (card->suit - 1) * m_card_size.y;
            clip.w = m_card_size.x - CRD_SPX;
            clip.h = m_card_size.y - CRD_SPYT - CRD_SPYB;

            SDL_BlitSurface( m_card_sprite, &clip, m_screen, pos );
        }
	}

    SDL_Rect *GetCardSize(void){

        return &m_card_size;
    }

private:

	SDL_Surface	*m_screen;
	SDL_Surface *m_card_sprite;
	SDL_Rect	m_card_size;
};

#endif
