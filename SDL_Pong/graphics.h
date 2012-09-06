#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

using namespace std;


//==============================================================================

SDL_Surface* load_image( std::string filename );

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );

//==============================================================================

#endif


