#include "SDL/SDL.h"
#include "Graphics.h"
#include "Timer.h"
#include "Ball.h"
#include "Bat.h"
#include "Menu.h"
using namespace std;

class Window
{
    private:
    //Whether the window is windowed or not
    bool windowed;

    //Whether the window is fine
    bool windowOK;

    public:
    Window();

    void handle_event(  SDL_Event );
    void toggle_fullscreen();
    bool error();
};






//G-G-G-Globle varibles
//------------------------------
const int SCREEN_HEIGHT = 600;
const int SCREEN_WIDTH = ( SCREEN_HEIGHT * 1.6 );
const int SCREEN_HEIGHT_FULL = 1050;
const int SCREEN_WIDTH_FULL = 1680;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 60;
//-----------------------------
SDL_Surface* Display = NULL;            //Our main display
//-----------------------------
SDL_Event event;                        //The event structure
//-----------------------------
//Making the objects and sending the globle varibles to them
//----------------------------------------------------------------------------------------------
Window Window;
Menu Menu;
Bat Player_1( SCREEN_WIDTH, SCREEN_HEIGHT, true ), Player_2( SCREEN_WIDTH, SCREEN_HEIGHT, false );
Ball Ball( SCREEN_WIDTH );
Timer Fps( FRAMES_PER_SECOND );
//-----------------------------
const int NO_SCORE = 0;
const int P1_SCORES = 1;
const int P2_SCORES = 2;
//-----------------------------







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
        if( event.resize.w < 600 )
            event.resize.w = 600;

        if( event.resize.h < 375 )
            event.resize.h = 375;

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
    else if( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_F1 ) )
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
        Display = SDL_SetVideoMode( SCREEN_WIDTH_FULL, SCREEN_HEIGHT_FULL, SCREEN_BPP, SDL_SWSURFACE | SDL_RESIZABLE | SDL_FULLSCREEN );

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

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
        return false;

    //If everything initialized fine
    return true;
}

void clean_up()
{
    //Free the surfaces before closing
    if( Display )
        SDL_FreeSurface( Display );

    //Quit SDL
    SDL_Quit();
}





int main( int argc, char* args[] )
{

    bool quit = false;
    bool show_menu = true;
    int score = 0;
    int cursor = 0;





    //setup-----------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------------
    if( init() == false )               //Starts up SDL and quits if there is a problem.
        return 1;
    //-----------------------------------------------------------------------------
	Player_1.Display = Display;         //Sets Player_1 to be able to blit onscreen
	Player_2.Display = Display;         //Sets Player_2 to be able to blit onscreen
	Ball.Display = Display;             //Sets Ball to be able to blit onscreen
	Menu.Display = Display;             //Sets Menu to be able to blit onscreen
    //------------------------------------------------------------------------------
    //Loads any needed files and quits if there is a problem.
    //----------------------------------------------------------------------------------------------
    if( ( Player_1.load_files() == false ) || ( Player_2.load_files() == false ) || ( Ball.load_files() == false ) || ( Menu.load_files() == false ) )
        return 1;
    //----------------------------------------------------------------------------------------------





    //Splash Screen then menu
    //----------------------------------------------------------------------------------------------
    Menu.logo();
    Menu.fade( "white" );






    //The main loop---------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------------
    while( quit == false )
    {
        if( ! ( Fps.is_paused() ) )
            Fps.start();

        //While there is an event to handle
        while( SDL_PollEvent( &event ) )
        {

            //Handle inputs for Player 1 anf 2
            //----------------------------------------------
            Player_1.handle_event( event );
            Player_2.handle_event( event );
            //Handles resizing of the window
            Window.handle_event( event );

            quit = Menu.handle_event( event );

            //----------------------------------------------

            //Handles resizing of the bat and ball
            //----------------------------------------------
            if( event.type == SDL_VIDEOEXPOSE || event.type == SDL_VIDEORESIZE )
            {
                Ball.resize();
                Player_1.resize();
                Player_2.resize();
            }
            //----------------------------------------------


            //If the user presses 'p' it will pause the game
            //----------------------------------------------
            if( ( event.type == SDL_KEYDOWN )  )
            {
                if( ( event.key.keysym.sym == SDLK_p ) && ( show_menu == false ) )
                {
                    if( Fps.is_paused() )
                        Fps.unpause();

                    else if( !( Fps.is_paused() ) )
                        Fps.pause();
                }

                if( event.key.keysym.sym == SDLK_ESCAPE )
                {
                    if( show_menu == true )
                        show_menu = false;

                    else if( show_menu == false )
                        show_menu = true;
                }

            }
            //----------------------------------------------
            if( event.type == SDL_QUIT )
            {
                quit = true;
            }


        }


        //Move Player 1 and 2 based on their inputs
        //----------------------------------------------
        if( !( Fps.is_paused() ) && ( show_menu == false ) )
        {
            Player_1.move();
            Player_2.move();

            //Move the ball and check for scores
            score = Ball.move( Player_1.hit_box, Player_2.hit_box );

            if( score == P1_SCORES )
                Player_1.score++;

            if( score == P2_SCORES )
                Player_2.score++;

            if ( score == P1_SCORES || score == P2_SCORES)
                Ball.reset();
        }
        //----------------------------------------------


        //Render-----------------------------------------------------------------------------------
        //-----------------------------------------------------------------------------------------
        SDL_FillRect( Display, &Display->clip_rect, SDL_MapRGB( Display->format, 0x00, 0x00, 0x00 ) );

        if( show_menu == false )
        {
            Player_1.render();
            Player_2.render();
            Ball.render();
        }

        if( show_menu == true )
            Menu.render();


        SDL_Flip( Display );
        Fps.frame_cap();
        //-----------------------------------------------------------------------------------------
    }
    //end of main loop------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------------

    //Clean up and quit SDL--------
    //-----------------------------
    Player_1.clean_up();
    Player_2.clean_up();
    Ball.clean_up();
    Menu.clean_up();
    clean_up();
    //-----------------------------
    return 0;
}

