#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "timer.h"
#include "table.h"

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


int main( int argc, char* args[] )
{
    //setup
    //----------------------------------------------------------------------------------------------
    bool quit = false;
    Timer fps( FRAMES_PER_SECOND );
    Table tic_tac_toe( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, CELL_WIDTH, CELL_HEIGHT );

    if( tic_tac_toe.init() == false )
        return 1;

    if( tic_tac_toe.load_files() == false )
        return 1;

    tic_tac_toe.set_clips();                    //Clips the sprite sheet for use
    tic_tac_toe.show_backround();               //and then applies the tiled backround

    if(  tic_tac_toe.update_screen() == false ) //Updates the screen and quits if there is a problem.
        return 1;

    //The main loop
    //----------------------------------------------------------------------------------------------
    while( quit == false )
    {
        fps.start();                            //Start the clock
        quit = ! tic_tac_toe.handle_event();    //Input is handled here. Yeah this line is a bit wierd. Its to handle if the user quits.
        tic_tac_toe.check_win();                //Guess what this does? :)
        fps.frame_cap();                        //Caps the frame rate

        if( ! tic_tac_toe.update_screen() )     //Updates the screen and quits if there is a problem.
            return 1;
    }
    //end of main loop
    //----------------------------------------------------------------------------------------------

    //Free the images and quit SDL
    tic_tac_toe.clean_up();

    return 0;
}
