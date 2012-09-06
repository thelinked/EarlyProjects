#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "graphics.h"
#include "Bat.h"

using namespace std;



TTF_Font* font = NULL;
//The color of the font
SDL_Color textColor = { 255, 255, 255 };

Bat::Bat( int SCREEN_WIDTH, int SCREEN_HEIGHT, bool choose_P1)
{
    //Surfaces
    Display = NULL;
    Surf_Sprite_Sheet = NULL;

    //Getting the globle varibles from main
    screen_width = SCREEN_WIDTH;
    screen_height = SCREEN_HEIGHT;


    //Setting up sprites
    clip_bat.x = 0;
    clip_bat.y = 0;
    clip_bat.w = 15;
    clip_bat.h = 100;

    score = 0;

    //Initialize the velocity
    xVel = 0;
    yVel = 0;


    //Setting up the hit box
    hit_box.w = 15;
    hit_box.h = 100;

    //Initialize the offsets for Player 1 and 2
    if( choose_P1 == true )
    {
        Player1 = true;
        hit_box.x = clip_bat.w;
        hit_box.y = ( screen_height / 2 ) - ( clip_bat.h / 2 );
    }
    else
    {
        Player1 = false;
        hit_box.x = screen_width - ( clip_bat.w * 2 );
        hit_box.y = ( screen_height / 2 ) - ( clip_bat.h / 2 );
    }
}

bool Bat::load_files()
{
    //Load the sprite map
    Surf_Sprite_Sheet = load_image( "resources/bat.png" );

    //Open the font
    font = TTF_OpenFont( "resources/visitor2.ttf", 90 );

    //If there was an problem loading the sprite map
    if( Surf_Sprite_Sheet == NULL )
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
    if ( Display )
        SDL_FreeSurface( Display );
    if( Surf_Message )
        SDL_FreeSurface( Surf_Message );

    //Close the font that was used
    TTF_CloseFont( font );
}

void Bat::handle_event( SDL_Event event )
{
    if ( Player1 )
    {
        //If a key was pressed
        if( event.type == SDL_KEYDOWN )
        {
        //Adjust the velocity
            switch( event.key.keysym.sym )
            {
                case SDLK_UP: yVel -= screen_height / 60; break;
                case SDLK_DOWN: yVel += screen_height / 60; break;
            }
        }
        //If a key was released
        else if( event.type == SDL_KEYUP )
        {
            //Adjust the velocity
            switch( event.key.keysym.sym )
            {
                case SDLK_UP: yVel += screen_height / 60; break;
                case SDLK_DOWN: yVel -= screen_height / 60; break;
            }
        }
    }

    if ( ! Player1 )
    {
        //If a key was pressed
        if( event.type == SDL_KEYDOWN )
        {
        //Adjust the velocity
            switch( event.key.keysym.sym )
            {
                case SDLK_w: yVel -= screen_height / 60; break;
                case SDLK_s: yVel += screen_height / 60; break;
            }
        }
        //If a key was released
        else if( event.type == SDL_KEYUP )
        {
            //Adjust the velocity
            switch( event.key.keysym.sym )
            {
                case SDLK_w: yVel += screen_height / 60; break;
                case SDLK_s: yVel -= screen_height / 60; break;
            }
        }
    }
}

void Bat::move()
{
    //Move the Bat up or down
    hit_box.y += yVel;

    //If the Bat went too far up or down
    if( ( hit_box.y < 0 ) || ( ( hit_box.y + clip_bat.h ) > screen_height ) )
    {
        //move back
        hit_box.y -= yVel;
    }
}

void Bat::sort_score()
{
    for(int i = 0; i < 10; i++ )
    {
        if(score == 0 )
            Surf_Message = TTF_RenderText_Solid( font, "0" , textColor );
        if(score == 1 )
            Surf_Message = TTF_RenderText_Solid( font, "1" , textColor );
        if(score == 2 )
            Surf_Message = TTF_RenderText_Solid( font, "2" , textColor );
        if(score == 3 )
            Surf_Message = TTF_RenderText_Solid( font, "3" , textColor );
        if(score == 4 )
            Surf_Message = TTF_RenderText_Solid( font, "4" , textColor );
        if(score == 5 )
            Surf_Message = TTF_RenderText_Solid( font, "5" , textColor );
        if(score == 6 )
            Surf_Message = TTF_RenderText_Solid( font, "6" , textColor );
        if(score == 7 )
            Surf_Message = TTF_RenderText_Solid( font, "7" , textColor );
        if(score == 8 )
            Surf_Message = TTF_RenderText_Solid( font, "8" , textColor );
        if(score == 9 )
            Surf_Message = TTF_RenderText_Solid( font, "9" , textColor );
    }
}

void Bat::render()
{
    //Show the dot
    apply_surface( hit_box.x, hit_box.y, Surf_Sprite_Sheet, Display, &clip_bat );
    //Render the text
    sort_score();

    if( Player1 )
        apply_surface( screen_width / 4, 0, Surf_Message, Display );
    if(! Player1 )
        apply_surface( ( screen_width / 4 ) * 3 , 0, Surf_Message, Display );
}
