#include <iostream>
#include <stdio.h>

#include "SDL.h"
#include "SDL_image.h"
#include "deck.h"
#include "table.h"
#include "card_blitter.h"
#include "table_blitter.h"
#include "screen.h"

#define LOOPS   1000

#define FPS 60

#define ASSETS_DIR "assets/"

using namespace std;

SDL_Rect card_size;

Card *card;
Deck deck;
Table table;

SDL_Window *window;
SDL_Renderer* renderer;
SDL_Surface *screen;
SDL_Surface *s_table;
SDL_Surface *cards;
SDL_Surface *pass;
SDL_Surface *fail;

typedef enum{

    r_fail,
    r_pass,
    quitted,
    r_in_progress

}e_result;

e_result done = r_in_progress;

bool cycle = false;

int Init_SDL(){

    if( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0)
    {
          cout <<"Could not initialize SDL: %S", SDL_GetError();
          return 0;
    }

    atexit(SDL_Quit);

    window = SDL_CreateWindow("PPasianssi",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      640, 480,
      0);

    if(window == NULL)
    {
          cout << "Could not set video mode: %S", SDL_GetError();
          return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if(renderer == NULL)
    {
      cout << "Could not create a renderer: %S", SDL_GetError();
      return 0;
    }

    screen = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0);

    if (!screen)
    {
      cout << "Could not create a surface: %S", SDL_GetError();
      return 0;
    }

    const Uint32 format = SDL_GetWindowPixelFormat( window );

    cards = load_image( format, ASSETS_DIR "cards2.png" );

    if(cards == NULL)
    {
          cout << "Could not load image";
          return 0;
    }

    s_table = load_image( format, ASSETS_DIR "table.png" );

    if(s_table == NULL)
    {
          cout << "Could not load image";
          return 0;
    }

    if((pass = load_image_alpha( ASSETS_DIR "pass.png" )) == NULL){
          cout << "Could not load image";
          return 0;
    }

    if((fail = load_image_alpha( ASSETS_DIR "fail.png" )) == NULL){
          cout << "Could not load image";
          return 0;
    }

    return 1;
}

void GetInput(){

    SDL_Event keyevent;

    while (SDL_PollEvent(&keyevent))
    {
        switch(keyevent.type){
            case SDL_KEYDOWN:
            {
                switch(keyevent.key.keysym.sym){
                    case SDLK_SPACE:
                        cycle = true;
                        break;
                    case SDLK_ESCAPE:
                        done = quitted;
                        break;
                    case SDLK_r:
                        deck.Shuffle();
                        table.Clear();
                        break;
                    default:
                        break;
                }

                break;
            }
            case SDL_MOUSEBUTTONDOWN:
                cycle = true;
                break;
            case SDL_QUIT:
            {
                done = quitted;
                break;
            }
        }
    }
}

void Update(){

    static uint8_t fail = 0;

    if(done == r_fail || done == r_pass){

        SDL_Delay(2000);

        deck.Shuffle();
        table.Clear();

        done = r_in_progress;
        cycle = false;

        SDL_Event keyevent;
        while (SDL_PollEvent(&keyevent))
            ;
    }

    if(cycle){

        cycle = false;

        card = deck.CurrentCard();

        if(card->rank == Card::no_rank)
            done = r_pass;

        if(!table.Push(card)){

            deck.PushBack();

            if(fail++ > deck.CardsLeft() + 1)
                done = r_fail;

        }else{

            deck.NextCard();
            fail = 0;
        }
    }
}

void Render(){

    SDL_Rect card_size, pos;

    card_size.x = 73;
    card_size.y = 98;

    TableBlitter TBlitter(screen, cards, &card_size);

    card = deck.CurrentCard();

    // Update the screen
    SDL_BlitSurface( s_table, NULL, screen, NULL );
    TBlitter.DrawTable(card, &table);

    pos.x = 150;
    pos.y = 150;

    if(done == r_fail){
        SDL_BlitSurface( fail, NULL, screen, &pos );
    }else if(done == r_pass){
        SDL_BlitSurface( pass, NULL, screen, &pos );
    }

    SDL_Texture *surface_texture = SDL_CreateTextureFromSurface( renderer, screen );
    SDL_RenderCopy( renderer, surface_texture, NULL, NULL );
    SDL_RenderPresent( renderer );
    SDL_DestroyTexture( surface_texture );
    SDL_RenderPresent( renderer );
}

int main(int argc, char *argv[])
{
    Uint32 waittime = (Uint32)(1000.0f / FPS);
    Uint32 framestarttime = 0;
    Sint32 delaytime;

    if(!Init_SDL()){
        return 0;
    }

    while(done != quitted){

        GetInput();
        Update();
        Render();

        delaytime = waittime - (SDL_GetTicks() - framestarttime);
        if(delaytime > 0)
            SDL_Delay((Uint32)delaytime);
        framestarttime = SDL_GetTicks();
    }

    if(screen)
      SDL_FreeSurface( screen );

    if(cards)
        SDL_FreeSurface( cards );

    if(s_table)
        SDL_FreeSurface( s_table );

    if(pass)
        SDL_FreeSurface( pass );

    if(fail)
        SDL_FreeSurface( fail );

    SDL_Quit();

    return 0;
}
