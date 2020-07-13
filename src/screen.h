#ifndef _SCREEN_H_
#define _SCREEN_H_

using namespace std;

#include <string>
#include "SDL.h"
#include "SDL_image.h"

SDL_Surface *load_image( Uint32 format, std::string filename, int r = -1, int g = -1, int b = -1 );
SDL_Surface *load_image_alpha( std::string filename );
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );

#endif
