#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "Timer.h"
#include "Table.h"
#include "Graphics.h"


using namespace std;



//G-G-G-Globle varibles
//------------------------------
const int SCREEN_WIDTH = 300;
const int SCREEN_HEIGHT = 240;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 60;
const int CELL_WIDTH = 100;
const int CELL_HEIGHT = 80;
//-----------------------------


//-----------------------------
SDL_Surface* Display = NULL;		//Our main display
SDL_Surface* Surf_Splash = NULL;    //Used for the splash Screen
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

    //Set the window caption
    SDL_WM_SetCaption( "TicTacToe", NULL );

    //Load the splash screen image
    Surf_Splash = load_image( "images/splash.png" );

    //If there was an problem loading
    if(  Surf_Splash == NULL )
        return false;

    //If everything initialized fine
    return true;
}

void splash_screen()
{
    apply_surface( 0, 0, Surf_Splash, Display );

    SDL_Flip( Display );

    SDL_Delay(1500);
}

void clean_up()
{
    //Free the surfaces before closing
    SDL_FreeSurface( Display );
    SDL_FreeSurface( Surf_Splash );
    //Quit SDL
    SDL_Quit();
}


int main( int argc, char* args[] )
{
    //setup
    //----------------------------------------------------------------------------------------------
    bool quit = false;

    //Making the objects and sending the globle varibles to them
    Timer fps( FRAMES_PER_SECOND );
    Table tic_tac_toe( SCREEN_WIDTH, SCREEN_HEIGHT, CELL_WIDTH, CELL_HEIGHT );
    //----------------------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------------------
    if( init() == false )                           //Starts up SDL and quits if there is a problem.
        return 1;

    if( tic_tac_toe.load_files() == false )         //Loads any needed files and quits if there is a problem.
        return 1;

	tic_tac_toe.Display = Display;                  //Sets the Table class to be able to blit onscreen

    splash_screen();                                 //Applies the splash screen to the Display surface then displays it

    tic_tac_toe.show_backround();                   //Applies the Backround to the Display surface then displays it

    SDL_Flip( Display );                            //Updates the screen
    //----------------------------------------------------------------------------------------------


    //The main loop. Its pretty clear what most of these functions are doing. Just remember that "SDL_Flip( Display );" updates the screen.
    //----------------------------------------------------------------------------------------------
    while( quit == false )
    {
        fps.start();
        if( tic_tac_toe.handle_event() == false )
            quit = true;

        SDL_Flip( Display );

        if( tic_tac_toe.check_win() )
        {
            tic_tac_toe.win();
            tic_tac_toe.restart();
        }

        else if ( tic_tac_toe.check_stalemate() )
            tic_tac_toe.restart();

        fps.frame_cap();
    }
    //end of main loop
    //----------------------------------------------------------------------------------------------

    //Clean up and quit SDL
    //----------------------------------------------------------------------------------------------
    tic_tac_toe.clean_up();
    clean_up();
    //----------------------------------------------------------------------------------------------
    return 0;
}
