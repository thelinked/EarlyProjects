#include "Graphics.h"

using namespace std;

SDL_Surface* load_image( std::string filename )
{
	SDL_Surface* loadedImage = IMG_Load(filename.c_str());
	SDL_Surface* optimizedImage = SDL_DisplayFormat( loadedImage );

	SDL_FreeSurface( loadedImage );

	return optimizedImage;
};


void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip  )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
};
