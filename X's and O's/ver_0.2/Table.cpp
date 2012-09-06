#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "timer.h"
#include "table.h"
#include <string>
using namespace std;





//Surfaces for blitting on screen
SDL_Surface *tile = NULL;
SDL_Surface *screen = NULL;


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

Table::Table( int SCREEN_WIDTH, int SCREEN_HEIGHT, int SCREEN_BPP, int CELL_WIDTH, int CELL_HEIGHT )
{
    xturn = true;
    screen_width = SCREEN_WIDTH;
    screen_height = SCREEN_HEIGHT;
    screen_bpp = SCREEN_BPP;
    cell_width = CELL_WIDTH;
    cell_height = CELL_HEIGHT;

    for( int i = 0; i < 3; i++)
    {
        for( int j = 0; j < 3; j++)
            grid[i][j] = '_';
    }
}

void Table::apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool Table::init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( screen_width, screen_height, screen_bpp, SDL_SWSURFACE );

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

bool Table::load_files()
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

void Table::clean_up()
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

bool Table::update_screen()
{
    if( SDL_Flip( screen ) == -1 )
    {
            return false;
    }
    else return true;
}

void Table::show_backround()
{
    for( int i = 0; i < ( screen_width ); i += cell_width )
    {
        for ( int j = 0; j < ( screen_height); j += cell_height )
            apply_surface( i, j, tile, screen, &clip_backround );
    }
}

bool Table::handle_event()
{
    int x, y;

    //If a mouse button was pressed
     while( SDL_PollEvent( &event ) )
        {
            if( event.type == SDL_QUIT )
            {
                return false;
            }

            //If there was a mouse event.
            if( event.type == SDL_MOUSEBUTTONDOWN )
            {
                //If the left mouse button was pressed
                if( event.button.button == SDL_BUTTON_LEFT )
                {
                    //go go integer rounding
                    x = event.button.x/cell_width;
                    y = event.button.y/cell_height;

                    //Adds the current move to an array if its a legal move. The array is then checked for victory conditions
                    //X's turn is tracked here too
                    if( xturn && ( grid[x][y] == '_' ) )
                    {
                        grid[x][y] = 'X';
                        apply_surface( event.button.x - 50, event.button.y - 40, tile, screen, &clip_o );
                        xturn = false;
                    }
                    else if( ( !xturn && grid[x][y] == '_' ) )
                    {
                        grid[x][y] = 'O';
                        apply_surface( event.button.x - 50, event.button.y - 40, tile, screen, &clip_x );
                        xturn = true;
                    }
                    //Adds the current move to an array storing all moves. The array is then checked for victory conditions



                }
            }
        }
        return true;
}

void Table::check_win()
{
    //Checking the first diagonal
    if ( ( grid[0][0] == grid[1][1] ) && ( grid[1][1] == grid[2][2] ) )
    {
        if( !( grid[0][0] == '_' ) )
            win();
    }

    //Checking the second diagonal
    else if ( ( grid[2][0] == grid[1][1] ) && ( grid[1][1] == grid[0][2] ) )
    {
        if( !( grid[2][0] == '_') )
            win();
    }

    //checking the rows
    for( int i = 0; i < 3; i++ )
    {
        if( ( grid[i][0] == grid[i][1] ) && ( grid[i][0] == grid[i][2] ) )
        {
            if( !( grid[i][0] == '_' ))
                win();
        }
    }
    //checking columns
    for( int j = 0; j < 3; j++ )
    {
        if( ( grid[0][j] == grid[1][j] ) && ( grid[0][j] == grid[2][j] ) )
        {
            if( !( grid[0][j] == '_' ))
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

    //Fill the screen white
    SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );


    //Reset the array and re-apply the tiled backround
    for( int i = 0; i < 3; i++)
    {
        for( int j = 0; j < 3; j++)
        {
            grid[i][j] = '_';
            apply_surface( cell_width * i, cell_height * j, tile, screen, &clip_backround );
        }
    }

 }
