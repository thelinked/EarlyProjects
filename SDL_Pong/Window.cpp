#include "SDL/SDL.h"
#include "Window.h"
using namespace std;

//G-G-G-Globle varibles
//------------------------------
const int SCREEN_HEIGHT = 600;
const int SCREEN_WIDTH = ( SCREEN_HEIGHT * 1.6 );
const int SCREEN_BPP = 32;

Window::Window()
{
    //Set up the screen
    Display = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_RESIZABLE );

    //If there's an error
    if( Display == NULL )
    {
        windowOK = false;
        return;
    }
    else
    {
        windowOK = true;
    }

    //Set the window caption
    SDL_WM_SetCaption( "2D Tennis", NULL );

    //Set window flag
    windowed = true;
}

void Window::handle_event( SDL_Event event )
{
    //If there's something wrong with the window
    if( windowOK == false )
    {
        return;
    }

    //If the window resized
    if( event.type == SDL_VIDEORESIZE )
    {
        //Resize the screen
        Display = SDL_SetVideoMode( event.resize.w, event.resize.h, SCREEN_BPP, SDL_SWSURFACE | SDL_RESIZABLE );

        //If there's an error
        if( Display == NULL )
        {
            windowOK = false;
            return;
        }
    }
    //If enter was pressed
    else if( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_RETURN ) )
    {
        //Turn fullscreen on/off
        toggle_fullscreen();
    }

    //If the window's screen has been altered
    else if( event.type == SDL_VIDEOEXPOSE )
    {
        //Update the screen
        if( SDL_Flip( Display ) == -1 )
        {
            //If there's an error
            windowOK = false;
            return;
        }
    }
}

void Window::toggle_fullscreen()
{
    //If the screen is windowed
    if( windowed == true )
    {
        //Set the screen to fullscreen
        Display = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_RESIZABLE | SDL_FULLSCREEN );

        //If there's an error
        if( Display == NULL )
        {
            windowOK = false;
            return;
        }

        //Set the window state flag
        windowed = false;
    }
    //If the screen is fullscreen
    else if( windowed == false )
    {
        //Window the screen
        Display = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_RESIZABLE );

        //If there's an error
        if( Display == NULL )
        {
            windowOK = false;
            return;
        }

        //Set the window state flag
        windowed = true;
    }
}

bool Window::error()
{
    return !windowOK;
}

