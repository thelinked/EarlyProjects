#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "Graphics.h"
#include "Timer.h"
#include "Ball.h"
#include "Bat.h"
#include "Splash_Screen.h"
using namespace std;

//G-G-G-Globle varibles
//------------------------------
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 60;
//-----------------------------
SDL_Surface* Display = NULL;            //Our main display
//-----------------------------
SDL_Event event;                        //The event structure
//-----------------------------
const int NO_SCORE = 0;
const int P1_SCORES = 1;
const int P2_SCORES = 2;
//-----------------------------

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
        return false;

    //Set up the screen
    Display = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    if( Display == NULL )
        return false;

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "2D Tennis", NULL );

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
    int score = 0;


    //Making the objects and sending the globle varibles to them
    //----------------------------------------------------------------------------------------------
    Bat Player_1( SCREEN_WIDTH, SCREEN_HEIGHT, true ), Player_2( SCREEN_WIDTH, SCREEN_HEIGHT, false );
    Ball Ball( SCREEN_WIDTH, SCREEN_HEIGHT );
    Timer Fps( FRAMES_PER_SECOND );
    Splash_Screen Splash( SCREEN_WIDTH, SCREEN_HEIGHT );
    //----------------------------------------------------------------------------------------------


    //setup
    //----------------------------------------------------------------------------------------------
    if( init() == false )               //Starts up SDL and quits if there is a problem.
        return 1;

    //Loads any needed files and quits if there is a problem.
    if( ( Player_1.load_files() == false ) || ( Player_2.load_files() == false ) || ( Ball.load_files() == false ) || ( Splash.load_files() == false ) )
        return 1;

	Player_1.Display = Display;         //Sets Player_1 to be able to blit onscreen
	Player_2.Display = Display;         //Sets Player_2 to be able to blit onscreen
	Ball.Display = Display;             //Sets Ball to be able to blit onscreen
	Splash.Display = Display;           //Sets Splash to be able to blit onscreen
    //----------------------------------------------------------------------------------------------


    //Splash Screen then menu
    Splash.logo();
    Splash.fade();
  //  Splash.show_instructions( event );


    //The main loop. Its pretty clear what most of these functions are doing. Just remember that "SDL_Flip( Display );" updates the screen.
    //----------------------------------------------------------------------------------------------
    while( quit == false )
    {
        Fps.start();
        //If a mouse button was pressed
        while( SDL_PollEvent( &event ) )
        {
            if( event.type == SDL_QUIT )
            {
                return 1;
            }
            //Handle inputs for Player 1 anf 2
            Player_1.handle_event( event );
            Player_2.handle_event( event );
        }

        //Move Player 1 and 2 based on their inputs
        Player_1.move();
        Player_2.move();

        //Move the ball and check for scores
        score = Ball.move( Player_1.hit_box, Player_2.hit_box );

        if( score == P1_SCORES )
        {
            Player_1.score++;
            Ball.reset();
        }
        if( score == P2_SCORES )
        {
            Player_2.score++;
            Ball.reset();
        }

        //Render
        //-----------------------------
        SDL_FillRect( Display, &Display->clip_rect, SDL_MapRGB( Display->format, 0x00, 0x00, 0x00 ) );
        Player_1.render();
        Player_2.render();
        Ball.render();
        SDL_Flip( Display );
        Fps.frame_cap();
        //-----------------------------
    }
    //end of main loop
    //----------------------------------------------------------------------------------------------

    //Clean up and quit SDL
    //-----------------------------
    Player_1.clean_up();
    Player_2.clean_up();
    clean_up();
    //-----------------------------
    return 0;
}
