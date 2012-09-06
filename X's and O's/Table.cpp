#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "table.h"
#include "timer.h"
#include "graphics.h"
#include <string>
using namespace std;



Table::Table( int SCREEN_WIDTH, int SCREEN_HEIGHT, int CELL_WIDTH, int CELL_HEIGHT )
{
    Display = NULL;

    //Surface for blitting on screen
    Surf_Sprite_Sheet = NULL;

    //Getting the globle varibles from main
    screen_width = SCREEN_WIDTH;
    screen_height = SCREEN_HEIGHT;
    cell_width = CELL_WIDTH;
    cell_height = CELL_HEIGHT;

    //setting up who will go first and clearing the array that stores moves.
    xturn = true;
    for( int i = 0; i < 3; i++)
    {
        for( int j = 0; j < 3; j++)
            grid[i][j] = '_';
    }

    //Setting up sprites

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

bool Table::load_files()
{
    //Load the sprite map
    Surf_Sprite_Sheet = load_image( "images/tile.png" );

    //If there was an problem loading the sprite map
    if( Surf_Sprite_Sheet == NULL )
    {
        return false;
    }
    return true;
}

void Table::clean_up()
{
    //Free the surfaces before closing
    SDL_FreeSurface( Surf_Sprite_Sheet );
    SDL_FreeSurface( Display );
}

void Table::show_backround()
{
    //Fill the screen white
    SDL_FillRect( Display, &Display->clip_rect, SDL_MapRGB( Display->format, 0xFF, 0xFF, 0xFF ) );

    //Tiles the backround with whatever is in clip_backround
    for( int i = 0; i < ( screen_width ); i += cell_width )
    {
        for ( int j = 0; j < ( screen_height); j += cell_height )
            apply_surface( i, j, Surf_Sprite_Sheet, Display, &clip_backround );
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
                    apply_surface( event.button.x - 50, event.button.y - 40, Surf_Sprite_Sheet, Display, &clip_o );
                    xturn = !xturn;
                }
                else if( ( !xturn && grid[x][y] == '_' ) )
                {
                    grid[x][y] = 'O';
                    apply_surface( event.button.x - 50, event.button.y - 40, Surf_Sprite_Sheet, Display, &clip_x );
                    xturn = !xturn;
                }
            }
        }
    }
    return true;
}

bool Table::check_win()
{
    //Checking the first diagonal
    if ( ( grid[0][0] == grid[1][1] ) && ( grid[1][1] == grid[2][2] ) )
    {
        if( !( grid[0][0] == '_' ) )
            return true;
    }

    //Checking the second diagonal
    else if ( ( grid[2][0] == grid[1][1] ) && ( grid[1][1] == grid[0][2] ) )
    {
        if( !( grid[2][0] == '_') )
            return true;
    }

    //checking the rows
    for( int i = 0; i < 3; i++ )
    {
        if( ( grid[i][0] == grid[i][1] ) && ( grid[i][0] == grid[i][2] ) )
        {
            if( !( grid[i][0] == '_' ))
            return true;
        }
    }
    //checking columns
    for( int j = 0; j < 3; j++ )
    {
        if( ( grid[0][j] == grid[1][j] ) && ( grid[0][j] == grid[2][j] ) )
        {
            if( !( grid[0][j] == '_' ))
            return true;
        }
    }
    return false;


}

 void Table::win()
 {
    //fill the screen black
    SDL_FillRect( Display, &Display->clip_rect, SDL_MapRGB( Display->format, 0x00, 0x00, 0x00 ) );

    //If it was X's turn then he won otherwise it was O.
    if(xturn)
        apply_surface(60 , 150 , Surf_Sprite_Sheet, Display, &clip_xwin );
    else if(!xturn)
        apply_surface(60 , 150 ,Surf_Sprite_Sheet, Display, &clip_owin );


    //Update the screen then delay befor going back to the main loop after restart()
    SDL_Flip( Display );
    SDL_Delay(1500);
 }

bool Table::check_stalemate()
{
    int move = 0;
    for( int i = 0; i < 3; i++)
    {
        for( int j = 0; j < 3; j++)
        {
            if(  ! ( grid[i][j] == '_' )  )
                move++;
            if( move >= 9 )
            {
                SDL_Delay(500);
                return true;
            }
        }
    }
    return false;
}

 void Table::restart()
 {
    //Reset the array and re-apply the tiled backround
    for( int i = 0; i < 3; i++ )
    {
        for( int j = 0; j < 3; j++ )
            grid[i][j] = '_';
    }

    show_backround();
 }
