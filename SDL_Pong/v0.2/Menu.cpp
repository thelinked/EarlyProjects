#include "SDL/SDL.h"
#include "graphics.h"
#include "timer.h"
#include "Menu.h"
using namespace std;

//This class isn't really needed. Everything could have been done in main but I'm trying new stuff like changing alpha between two surfaces and animation so I kept it seperate.

Menu::Menu()
{
    //Surfaces
    Display = NULL;
    Surf_Menu_Black = NULL;
    Surf_Menu_White = NULL;

    Surf_Logo_Sprite = NULL;
    Surf_Menu_Sprite = NULL;

    //Menu_Timer(60);
    cursor = 0;

    alpha = SDL_ALPHA_TRANSPARENT;

    for( int i = 0; i < 12; i++ )
    {
        rect_menu_logo[ i ].x = 0;
        rect_menu_logo[ i ].y = 0 + ( i * 67 );
        rect_menu_logo[ i ].w = 480;
        rect_menu_logo[ i ].h = 67;
    }

    rect_menu[0].x = 0;
    rect_menu[0].y = 0;
    rect_menu[0].w = 310;
    rect_menu[0].h = 160;

    rect_menu[1].x = 0;
    rect_menu[1].y = 160;
    rect_menu[1].w = 40;
    rect_menu[1].h = 40;

}

bool Menu::load_files()
{
    //Load the splash screen image
    Surf_Logo_Sprite = load_image( "resources/logo_sprite_sheet.png" );
    Surf_Menu_Sprite = load_image( "resources/menu_sprite_sheet.png" );

    Surf_Menu_Black = load_image( "resources/black.png" );
    Surf_Menu_White = load_image( "resources/white.png" );


    //SDL_FillRect( Surf_Menu_White, &Display->clip_rect, SDL_MapRGB( Display->format, 0xFF, 0xFF, 0xFF ) );
    //SDL_FillRect( Surf_Menu_Black, &Display->clip_rect, SDL_MapRGB( Display->format, 0x00, 0x00, 0x00 ) );

    //If there was an problem loading the images
    if(  Surf_Logo_Sprite == NULL || Surf_Menu_Sprite == NULL || Surf_Menu_Black == NULL /*|| Surf_Menu_White == NULL*/  )
        return false;

    return true;
}

void Menu::clean_up()
{
    //Free the surfaces before closing
    if( Surf_Logo_Sprite )
        SDL_FreeSurface( Surf_Logo_Sprite );

    if( Surf_Menu_Sprite )
        SDL_FreeSurface( Surf_Menu_Sprite );


    if( Surf_Menu_Black )
        SDL_FreeSurface( Surf_Menu_Black );

    if( Surf_Menu_White )
        SDL_FreeSurface( Surf_Menu_White );
}

//The first part. Displays number_12 logo. Demonstrates Animation
void Menu::logo()
{
    Timer logo_timer( 12 );


    SDL_FillRect( Display, &Display->clip_rect, SDL_MapRGB( Display->format, 0xFF, 0xFF, 0xFF ) );
    for( int i = 0; i < 11; i++ )
    {
        //Keeps the screen responsive
        while( SDL_PollEvent( &event ) ) { }

        logo_timer.start();
        apply_surface( ( Display->w / 2) - ( rect_menu_logo[0].w / 2) , ( Display->h / 2) - ( rect_menu_logo[0].h / 2), Surf_Logo_Sprite, Display, &rect_menu_logo[i] );
        SDL_Flip( Display );
        logo_timer.frame_cap();
    }

    for( int i = 11; i > 0; i-- )
    {
        //Keeps the screen responsive
        while( SDL_PollEvent( &event ) ) { }

        logo_timer.start();
        apply_surface( ( Display->w / 2) - ( rect_menu_logo[0].w / 2) , ( Display->h / 2) - ( rect_menu_logo[0].h / 2), Surf_Logo_Sprite, Display, &rect_menu_logo[i] );
        SDL_Flip( Display );
        logo_timer.frame_cap();
    }
    SDL_Delay( 1000 );
}

//The second part.  Demonstrates Alpha Blending
void Menu::fade( std::string colour )
{
    Timer Menu_Timer(60);
    alpha = 15;


    SDL_SetAlpha( Surf_Menu_Black, SDL_SRCALPHA, alpha );
    SDL_SetAlpha( Surf_Menu_White, SDL_SRCALPHA, alpha );

    for( int i = 0; i < 40; i++ )
    {
        //Keeps the screen responsive
        while( SDL_PollEvent( &event ) ) { }

        Menu_Timer.start();
        if( colour == "black" )
            apply_surface( 0, 0, Surf_Menu_Black, Display );
        else if( colour == "white" )
            apply_surface( 0, 0, Surf_Menu_White, Display );
        SDL_Flip( Display );
        Menu_Timer.frame_cap();
    }
}

void Menu::render()
{
    int offsetX = ( Display->w - rect_menu[0].w ) / 2;
    int offsetY = ( Display->h - rect_menu[0].h ) / 2;

    int offsetX_cursor = ( Display->w - rect_menu[0].w ) / 2 -  rect_menu[1].w;
    int offsetY_cursor = ( Display->h - rect_menu[0].h ) / 2 + ( rect_menu[1].h * cursor );


    SDL_FillRect( Display, &Display->clip_rect, SDL_MapRGB( Display->format, 0xFF, 0xFF, 0xFF ) );

    apply_surface( offsetX, offsetY , Surf_Menu_Sprite, Display, &rect_menu[0] );
    apply_surface( offsetX_cursor, offsetY_cursor , Surf_Menu_Sprite, Display, &rect_menu[1] );

    SDL_Flip( Display );
}

bool Menu::handle_event( SDL_Event event )
{
    //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
    //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_UP:
            if( cursor != 0 )
                cursor--;
            return false;

            case SDLK_DOWN:
            if( cursor != 3 )
                cursor++;
            return false;

            case SDLK_RETURN:

            switch( cursor )
            {
                case 0:
                return false;


                case 1:
                return false;


                case 2:
                return false;

                case 3:
                return true;

            }
        }
    }

    return false;
}

void Menu::show_instructions()
{
}
