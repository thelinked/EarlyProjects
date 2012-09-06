#include "SDL/SDL.h"
#include "graphics.h"
#include "timer.h"
#include "Splash_Screen.h"
using namespace std;

//This class isn't really needed. Everything could have been done in main but I'm trying new stuff like changing alpha between two surfaces and animation so I kept it seperate.

Splash_Screen::Splash_Screen( int SCREEN_WIDTH, int SCREEN_HEIGHT )
{
    //Surfaces
    Display = NULL;
    Surf_Splash_Front = NULL;
    Surf_Splash_Sprite = NULL;

    //Getting the globle varibles from main
    screen_width = SCREEN_WIDTH;
    screen_height = SCREEN_HEIGHT;

    alpha = SDL_ALPHA_TRANSPARENT;

    for( int i = 0; i < 11; i++ )
    {
        rect_splash_screen[ i ].x = 0;
        rect_splash_screen[ i ].y = 0 + ( i * 67 );
        rect_splash_screen[ i ].w = 480;
        rect_splash_screen[ i ].h = 67;
    }

    offsetX = ( ( screen_width / 2) - ( rect_splash_screen[0].w / 2) );
    offsetY = ( ( screen_height / 2) - ( rect_splash_screen[0].h / 2) );

}

bool Splash_Screen::load_files()
{
    //Load the splash screen image
    Surf_Splash_Sprite = load_image( "resources/splash_sprite_sheet.png" );
    Surf_Splash_Front = load_image( "resources/fade.png" );

    //If there was an problem loading the images
    if(  Surf_Splash_Sprite == NULL || Surf_Splash_Front == NULL )
        return false;

    return true;
}

void Splash_Screen::clean_up()
{
    //Free the surfaces before closing
    if ( Display )
        SDL_FreeSurface( Display );
    if( Surf_Splash_Sprite )
        SDL_FreeSurface( Surf_Splash_Sprite );
    if( Surf_Splash_Front )
        SDL_FreeSurface( Surf_Splash_Front );
}

//The first part. Displays number_12 logo. Demonstrates Animation
void Splash_Screen::logo()
{
    Timer logo_timer( 12 );


    SDL_FillRect( Display, &Display->clip_rect, SDL_MapRGB( Display->format, 0xFF, 0xFF, 0xFF ) );
    for( int i = 0; i < 11; i++ )
    {
        logo_timer.start();
        apply_surface( offsetX, offsetY, Surf_Splash_Sprite, Display, &rect_splash_screen[i] );
        SDL_Flip( Display );
        logo_timer.frame_cap();
    }

    for( int i = 11; i > 0; i-- )
    {
        logo_timer.start();
        apply_surface( offsetX, offsetY, Surf_Splash_Sprite, Display, &rect_splash_screen[i] );
        SDL_Flip( Display );
        logo_timer.frame_cap();
    }
    SDL_Delay( 1500 );
}

//The second part.  Demonstrates Alpha Blending
void Splash_Screen::fade()
{
    Timer Splash_Timer( 60 );


    //Fade to black
    for( alpha; alpha < SDL_ALPHA_OPAQUE; alpha += 10 )
    {   Splash_Timer.start();
        //Set surface alpha
        SDL_SetAlpha( Surf_Splash_Front, SDL_SRCALPHA, alpha );

        SDL_FillRect( Display, &Display->clip_rect, SDL_MapRGB( Display->format, 0xFF, 0xFF, 0xFF ) );
        apply_surface( offsetX, offsetY, Surf_Splash_Sprite, Display, &rect_splash_screen[0] );
        apply_surface( 0, 0, Surf_Splash_Front, Display );

        SDL_Flip( Display );
        Splash_Timer.frame_cap();
    }
}
/*
void Splash_Screen::show_instructions( SDL_Event event )
{
}
*/
