#include "SDL/SDL.h"
#include "Ball.h"
#include "graphics.h"
using namespace std;



Ball::Ball( int SCREEN_WIDTH, int SCREEN_HEIGHT )
{
    //Surfaces
    Display = NULL;
    Surf_Sprite_Sheet = NULL;

    //Getting the globle varibles from main
    screen_width = SCREEN_WIDTH;
    screen_height = SCREEN_HEIGHT;


    //Setting up sprites
    clip_ball.x = 0;
    clip_ball.y = 0;
    clip_ball.w = 15;
    clip_ball.h = 15;

    //Setting up collision box
    hit_box.w = 15;
    hit_box.h = 15;
    hit_box.x = ( screen_width / 2 ) - ( clip_ball.w / 2 );
    hit_box.y = ( screen_height / 2 ) - ( clip_ball.h / 2 );

    //Initialize the velocity
    xVel = ( screen_height / 100 );
    yVel = ( screen_height / 200 );
}

bool Ball::load_files()
{
    //Load the sprite map
    Surf_Sprite_Sheet = load_image( "resources/bat.png" );

    //If there was an problem loading the sprite map
    if( Surf_Sprite_Sheet == NULL )
    {
        return false;
    }
    return true;
}

void Ball::clean_up()
{
    //Free the surfaces before closing
    if( Surf_Sprite_Sheet )
        SDL_FreeSurface( Surf_Sprite_Sheet );
    if ( Display )
        SDL_FreeSurface( Display );
}


int Ball::move( SDL_Rect P1_hit_box, SDL_Rect P2_hit_box )
{
    //Move the square up or down
    hit_box.y += yVel;

    //If the square went too far up or down or has collided with the wall
    if( ( hit_box.y < 0 ) || ( hit_box.y + clip_ball.h > screen_height ) || ( check_collision( hit_box, P1_hit_box ) ) || ( check_collision( hit_box, P2_hit_box ) ) )
    {
        //hit_box.y -= yVel;
        yVel = - yVel;
        if( yVel )
            yVel += ( screen_height / 500 );
        if( yVel < 0 )
            yVel -= (screen_height / 500 );

        //Right side of the screen
        if( hit_box.y + clip_ball.h > screen_height)
            hit_box.y = screen_height - clip_ball.h;

        //Left side of the screen
        if( hit_box.y < 0 )
            hit_box.y = 0;

        //The Left bat
        if( check_collision( hit_box, P1_hit_box ) )
            hit_box.x = P1_hit_box.x - P1_hit_box.w;

        //The right bat
        if( check_collision( hit_box, P2_hit_box ) )
            hit_box.y = P2_hit_box.y - P2_hit_box.w;
    }


    //Move the square left or right
    hit_box.x += xVel;

    //If the square went too far to the left or right or has collided with something
    if( ( hit_box.x < 0 ) || ( hit_box.x + clip_ball.w > screen_width ) || ( check_collision( hit_box, P1_hit_box ) ) || ( check_collision( hit_box, P2_hit_box ) ) )
    {
        //hit_box.x -= xVel;
        if( xVel )
            xVel += ( screen_height / 500 );
        if( xVel < 0 )
            xVel -= (screen_height / 500 );
        xVel = - xVel;

        //Right side of the screen
        if( hit_box.x + clip_ball.w > screen_width)
        {
            hit_box.x = screen_width - clip_ball.w;
            return 1;
        }

        //Left side of the screen
        if( hit_box.x < 0 )
        {
            hit_box.x = 0;
            return 2;
        }

        //The Left bat
        if( check_collision( hit_box, P1_hit_box ) )
            hit_box.x = P1_hit_box.x + P1_hit_box.w;

        //The right bat
        if( check_collision( hit_box, P2_hit_box ) )
            hit_box.x = P2_hit_box.x - P2_hit_box.w;
    }

    return 0;
}

bool Ball::check_collision( SDL_Rect A, SDL_Rect B )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

void Ball::reset()
{
    hit_box.x = ( screen_width / 2 ) - ( clip_ball.w / 2 );
    hit_box.y = ( screen_height / 2 ) - ( clip_ball.h / 2 );

    //Initialize the velocity
    xVel = ( screen_height / 200 );
    yVel = ( screen_height / 200 );

}

void Ball::render()
{
    //Show the dot
    apply_surface( hit_box.x, hit_box.y, Surf_Sprite_Sheet, Display, &clip_ball );
}

/*
int Ball::move( SDL_Rect P1_hit_box, SDL_Rect P2_hit_box )
{
    //Move the square up or down
    hit_box.y += yVel;

    //If the square went too far up or down or has collided with the wall
    if( ( hit_box.y < 0 ) || ( hit_box.y + clip_ball.h > screen_height ) || ( check_collision( hit_box, P1_hit_box ) ) || ( check_collision( hit_box, P2_hit_box ) ) )
    {
        //hit_box.y -= yVel;
        yVel = - yVel;
        if( yVel )
            yVel += ( screen_height / 500 );
        if( yVel < 0 )
            yVel -= (screen_height / 500 );

        //Right side of the screen
        if( hit_box.y + clip_ball.h > screen_height)
            hit_box.y = screen_height - clip_ball.h;

        //Left side of the screen
        if( hit_box.y < 0 )
            hit_box.y = 0;

        //The Left bat
        if( check_collision( hit_box, P1_hit_box ) )
            hit_box.x = P1_hit_box.x - P1_hit_box.w;

        //The right bat
        if( check_collision( hit_box, P2_hit_box ) )
            hit_box.y = P2_hit_box.y - P2_hit_box.w;
    }


    //Move the square left or right
    hit_box.x += xVel;

    //If the square went too far to the left or right or has collided with something
    if( ( hit_box.x < 0 ) || ( hit_box.x + clip_ball.w > screen_width ) || ( check_collision( hit_box, P1_hit_box ) ) || ( check_collision( hit_box, P2_hit_box ) ) )
    {
        //hit_box.x -= xVel;
        if( xVel )
            xVel += ( screen_height / 500 );
        if( xVel < 0 )
            xVel -= (screen_height / 500 );
        xVel = - xVel;

        //Right side of the screen
        if( hit_box.x + clip_ball.w > screen_width)
        {
            hit_box.x = screen_width - clip_ball.w;
            return 1;
        }

        //Left side of the screen
        if( hit_box.x < 0 )
        {
            hit_box.x = 0;
            return 2;
        }

        //The Left bat
        if( check_collision( hit_box, P1_hit_box ) )
            hit_box.x = P1_hit_box.x + P1_hit_box.w;

        //The right bat
        if( check_collision( hit_box, P2_hit_box ) )
            hit_box.x = P2_hit_box.x - P2_hit_box.w;
    }

    return 0;
}
*/
