#include "SDL/SDL.h"
#include "graphics.h"
#include "Bat.h"

using namespace std;




SDL_Color textColor = { 255, 255, 255 };

Bat::Bat( int SCREEN_WIDTH, int SCREEN_HEIGHT, bool choose_P1)
{
    //Surfaces
    Display = NULL;
    Surf_Sprite_Sheet = NULL;

    score = 0;

    //Setting up sprites
    for( int i = 0; i < 10; i++ )
    {
        clip_font[i].x = i * 24;
        clip_font[i].y = 0;
        clip_font[i].w = 24;
        clip_font[i].h = 24;
    }

    clip_bat.x = 0;
    clip_bat.y = 0;
    clip_bat.w = ( SCREEN_WIDTH / 64 );
    clip_bat.h = ( SCREEN_WIDTH / 10 );

    //Setting up the hit box
    hit_box.w = ( SCREEN_WIDTH / 64 );
    hit_box.h = ( SCREEN_WIDTH / 10 );

    //Initialize the velocity
    xVel = 0;
    yVel = 0;

    //Initialise the offsets amd controls for Player 1 and 2
    if( choose_P1 )
    {
        Player1 = true;
        control_up = SDLK_UP;
        control_down = SDLK_DOWN;

        hit_box.x = clip_bat.w;
        hit_box.y = ( SCREEN_HEIGHT / 2 ) - ( clip_bat.h / 2 );
    }
    else
    {
        Player1 = false;
        control_up = SDLK_w;
        control_down = SDLK_s;

        hit_box.x = SCREEN_WIDTH - ( clip_bat.w * 2 );
        hit_box.y = ( SCREEN_HEIGHT / 2 ) - ( clip_bat.h / 2 );
    }

}

bool Bat::load_files()
{
    //Load the sprite map
    Surf_Sprite_Sheet = load_image( "resources/bat.png" );
    Surf_Score_Sheet = load_image( "resources/font.png" );


    //If there was an problem loading the sprite map
    if( Surf_Sprite_Sheet == NULL ||  Surf_Score_Sheet == NULL )
    {
        return false;
    }
    return true;
}

void Bat::clean_up()
{
    //Free the surfaces before closing
    if( Surf_Sprite_Sheet )
        SDL_FreeSurface( Surf_Sprite_Sheet );

    if( Surf_Score_Sheet )
        SDL_FreeSurface( Surf_Score_Sheet );

}

void Bat::handle_event( SDL_Event event )
{
    //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
    //Adjust the velocity
        if( event.key.keysym.sym == control_up )
            yVel -= Display->h / 60;

        if( event.key.keysym.sym == control_down )
            yVel += Display->h / 60;
    }

    //If a key was released
    else if( event.type == SDL_KEYUP )
    {
        //Adjust the velocity
        if( event.key.keysym.sym == control_up )
            yVel += Display->h / 60;

        if( event.key.keysym.sym == control_down )
            yVel -= Display->h / 60;
    }

}

void Bat::move()
{
    //Move the Bat up or down
    hit_box.y += yVel;

    //If the Bat went too far up or down
    if( ( hit_box.y < 0 ) || ( ( hit_box.y + clip_bat.h ) > Display->h ) )
    {
        //move back
        hit_box.y -= yVel;
    }
}

void Bat::resize()
{
    //Setting up sprites
    clip_bat.x = 0;
    clip_bat.y = 0;
    clip_bat.w = ( Display->w / 64 );
    clip_bat.h = ( Display->w / 10 );

    //Setting up the hit box
    hit_box.w = ( Display->w / 64 );
    hit_box.h = ( Display->w / 10 );



    //Initialize the offsets for Player 1 and 2
    if( Player1 == true )
    {
        hit_box.x = clip_bat.w;
        hit_box.y = ( Display->h / 2 ) - ( clip_bat.h / 2 );
    }
    else
    {
        Player1 = false;
        hit_box.x = Display->w - ( clip_bat.w * 2 );
        hit_box.y = ( Display->h / 2 ) - ( clip_bat.h / 2 );
    }
}

void Bat::render()
{
    //Show the dot
    apply_surface( hit_box.x, hit_box.y, Surf_Sprite_Sheet, Display, &clip_bat );
    //Render the text
    //Massive Massive Memery leak was here. : )
    if( score > 9 )
        score = 0;

    for( int i = 0; i < 10; i++ )
    {
        if( score == i )
        {
            if( Player1 )
                apply_surface( Display->w / 4, Display->h / 32, Surf_Score_Sheet, Display, &clip_font[i] );
            if(! Player1 )
                apply_surface( ( Display->w / 4 ) * 3 , Display->h / 32, Surf_Score_Sheet, Display, &clip_font[i] );
        }
    }
}
