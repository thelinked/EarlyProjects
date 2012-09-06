#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "timer.h"

using namespace std;

//G-G-G-Globle varibles
//------------------------------
const int SCREEN_WIDTH = 300;
const int SCREEN_HEIGHT = 240;
const int SCREEN_BPP = 32;
const int frames_per_second = 60;
const int WIDTH = 100;
const int HEIGHT = 80;
//-----------------------------


//Surfaces for blitting on screen
SDL_Surface *tile = NULL;
SDL_Surface *screen = NULL;

//The portions of the sprite map to be blitted
SDL_Rect clip_backround;
SDL_Rect clip_x;
SDL_Rect clip_o;
SDL_Rect clip_xwin;
SDL_Rect clip_owin;
SDL_Rect clip_restart;

//The event structure
SDL_Event event;


class Table
{
    private:
    //Tables Varibles

    char grid[3][3];
    int cell_width;
    int cell_height;
    bool xturn;

    public:
    //Tables Functions
    Table();
    void set_clips();
    void show_backround();
    void handle_event();
    void check_win();
    void win();
    void restart();
};


Table::Table()
{
    xturn = true;

    cell_width = WIDTH;
    cell_height = HEIGHT;

    for( int i = 0; i < 3; i++)
    {
        for( int j = 0; j < 3; j++)
            grid[i][j] = 'A';
    }
}

SDL_Surface *load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormatAlpha( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );
    }

    //Return the optimized surface
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "TicTacToe", NULL );

    //If everything initialized fine
    return true;
}

bool load_files()
{
    //Load the sprite map
    tile = load_image( "images/tile.png" );

    //If there was an problem loading the sprite map
    if( tile == NULL )
    {
        return false;
    }
    return true;
}

void clean_up()
{
    //Free the sprite map
    SDL_FreeSurface( tile );

    //Quit SDL
    SDL_Quit();
}

void Table::set_clips()
{

    //Clip range for the backround
    clip_backround.x = 0;
    clip_backround.y = 0;
    clip_backround.w = cell_width;
    clip_backround.h = cell_height;

    //Clip range for O
    clip_o.x = cell_width;
    clip_o.y = 0;
    clip_o.w = cell_width;
    clip_o.h = cell_height;

    //Clip range for X
    clip_x.x = ( cell_width * 2 ) ;
    clip_x.y = 0;
    clip_x.w = cell_width;
    clip_x.h = cell_height;

    //Clip range for O Win
    clip_owin.x = 115;
    clip_owin.y = 90;
    clip_owin.w = 185;
    clip_owin.h = 53;

    //Clip range for X Win
    clip_xwin.x = 115;
    clip_xwin.y = 140;
    clip_xwin.w = 185;
    clip_xwin.h = 57;

    //Clip range for Restart
    clip_restart.x = 0;
    clip_restart.y = 130;
    clip_restart.w = 105;
    clip_restart.h = 80;
}

void Table::show_backround()
{
    for( int i = 0; i < ( SCREEN_WIDTH ); i += cell_width )
    {
        for ( int j = 0; j < ( SCREEN_HEIGHT); j += cell_height )
            apply_surface( i, j, tile, screen, &clip_backround );
    }
}

void Table::handle_event()
{
    int x,y;
    //If a mouse button was pressed
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        //If the left mouse button was pressed
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            x = event.button.x/cell_width;
            y = event.button.y/cell_height;

            if(xturn && grid[x][y] == 'A')
            {
                apply_surface( event.button.x - 50, event.button.y - 40, tile, screen, &clip_o );
                xturn = false;
            }
            else if(!xturn && grid[x][y] == 'A')
            {
                apply_surface( event.button.x - 50, event.button.y - 40, tile, screen, &clip_x );
                    xturn = true;
            }
            //Adds the current move to an array storing all moves. The array is then checked for victory conditions
            if(xturn)
                grid[x][y] = 'X';
            else
                grid[x][y] = 'O';


            //Guess what this does? :)
            check_win();
        }
    }
}

void Table::check_win()
{
    //Checking the first diagonal
    if ( ( grid[0][0] == grid[1][1] ) && ( grid[1][1] == grid[2][2] ) )
    {
        if( !( grid[0][0] == 'A' ) )
            win();
    }

    //Checking the second diagonal
    else if ( ( grid[2][0] == grid[1][1] ) && ( grid[1][1] == grid[0][2] ) )
    {
        if( !( grid[2][0] == 'A') )
            win();
    }

    //checking the rows
    for( int i = 0; i < 3; i++ )
    {
        if( ( grid[i][0] == grid[i][1] ) && ( grid[i][0] == grid[i][2] ) )
        {
            if( !( grid[i][0] == 'A' ))
                win();
        }
    }
    //checking columns
    for( int j = 0; j < 3; j++ )
    {
        if( ( grid[0][j] == grid[1][j] ) && ( grid[0][j] == grid[2][j] ) )
        {
            if( !( grid[0][j] == 'A' ))
                win();
        }
    }


}

 void Table::win()
 {
    SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ) );

    if(xturn)
        apply_surface(60 , 150 , tile, screen, &clip_xwin );
    else if(!xturn)
        apply_surface(60 , 150 ,tile, screen, &clip_owin );
    SDL_Flip( screen );
    SDL_Delay(1500);

    restart();
 }

 void Table::restart()
 {

    for( int i = 0; i < 3; i++)
    {
        for( int j = 0; j < 3; j++)
            grid[i][j] = 'A';
    }

    //Fill the screen white
    SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );


    //Apply the tiled backround
    for( int i = 0; i < 300; i += 100 )
    {
        for ( int j = 0; j < 240; j += 80 )
            apply_surface( i, j, tile, screen, &clip_backround );
    }

 }


int main( int argc, char* args[] )
{

    //setup
    //----------------------------------------------------------------------------------------------
    bool quit = false;
    Timer fps(frames_per_second);
    Table tic_tac_toe;


    if( init() == false )
    {
        return 1;
    }

    if( load_files() == false )
    {
        return 1;
    }


    //Fill the screen white
    SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );


    //Clip the sprite sheet
    tic_tac_toe.set_clips();
    //Apply the tiled backround
    tic_tac_toe.show_backround();

    //Update the screen
    if( SDL_Flip( screen ) == -1 )
    {
        return 1;
    }
    //end of setup
    //----------------------------------------------------------------------------------------------
    //The main loop
    //----------------------------------------------------------------------------------------------
    while( quit == false )
    {
        //Start the fps clock
        fps.start();

        //This is the loop that handles input
        while( SDL_PollEvent( &event ) )
        {
            if( event.type == SDL_QUIT )
            {
                quit = true;
            }

            tic_tac_toe.handle_event();
        }

        //Cap the frame rate
        fps.frame_cap();
        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
                return 1;
        }
    }
    //end of main loop
    //----------------------------------------------------------------------------------------------


    //Free the images and quit SDL
    clean_up();

    return 0;
}
