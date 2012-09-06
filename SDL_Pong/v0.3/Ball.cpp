#include "SDL/SDL.h"
#include "Ball.h"
#include "graphics.h"
#include "time.h"
using namespace std;



Ball::Ball( int SCREEN_WIDTH )
{
    //Surfaces
    Display = NULL;
    Surf_Sprite_Sheet = NULL;



    //Setting up sprites
    clip_ball.x = 0;
    clip_ball.y = 0;
    clip_ball.w = ( SCREEN_WIDTH / 64 );
    clip_ball.h = ( SCREEN_WIDTH / 64 );

    //Setting up collision box
    hit_box.x = ( SCREEN_WIDTH / 2 ) - ( clip_ball.w / 2 );
    hit_box.y = ( SCREEN_WIDTH / 2 ) - ( clip_ball.h / 2 );
    hit_box.w = ( SCREEN_WIDTH / 64 );
    hit_box.h = ( SCREEN_WIDTH / 64 );


	srand( (unsigned)time(NULL) );

    //Initialize the velocity
    xVel = ( ( SCREEN_WIDTH / 480 ) + ( rand()%( SCREEN_WIDTH / 320 ) )  );
    yVel = ( SCREEN_WIDTH / 320 );
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
}


int Ball::move( SDL_Rect P1_hit_box, SDL_Rect P2_hit_box )
{
    //Move the square up or down
    hit_box.y += yVel;

    //If the square went too far up or down or has collided with the wall
    if( ( hit_box.y < 0 ) || ( hit_box.y + clip_ball.h > Display->h ) || ( check_collision( hit_box, P1_hit_box ) ) || ( check_collision( hit_box, P2_hit_box ) ) )
    {
        //hit_box.y -= yVel;
        yVel = - yVel;
        if( yVel )
            yVel += ( Display->w / 800 );
        if( yVel < 0 )
            yVel -= (Display->w / 800 );

        //Right side of the screen
        if( hit_box.y + clip_ball.h > Display->h)
            hit_box.y = Display->h - clip_ball.h;

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
    if( ( hit_box.x < 0 ) || ( hit_box.x + clip_ball.w > Display->w ) || ( check_collision( hit_box, P1_hit_box ) ) || ( check_collision( hit_box, P2_hit_box ) ) )
    {
        //hit_box.x -= xVel;
        if( xVel )
            xVel += ( Display->h / 500 );
        if( xVel < 0 )
            xVel -= (Display->h / 500 );
        xVel = - xVel;

        //Right side of the screen
        if( hit_box.x + clip_ball.w > Display->w)
        {
            hit_box.x = Display->w - clip_ball.w;
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
    hit_box.x = ( Display->w / 2 ) - ( clip_ball.w / 2 );
    hit_box.y = ( Display->h / 2 ) - ( clip_ball.h / 2 );



    //Initialize the velocity
    xVel = ( ( Display->w / 480 ) + ( rand()%( Display->w / 320 ) )  );
    yVel = ( Display->w / 320 );

    if( rand()%( 2 ) )
        xVel = -xVel;

    if( rand()%( 2 ) )
        yVel = -yVel;

}

void Ball::resize()
{
    //Setting up sprites
    clip_ball.x = 0;
    clip_ball.y = 0;
    clip_ball.w = ( Display->w / 64 );
    clip_ball.h = ( Display->w / 64 );

    //Setting up collision box
    hit_box.x = ( Display->w / 2 ) - ( clip_ball.w / 2 );
    hit_box.y = ( Display->h / 2 ) - ( clip_ball.h / 2 );
    hit_box.w = ( Display->w / 64 );
    hit_box.h = ( Display->w / 64 );


    //Initialize the velocity
    xVel = ( ( Display->w / 480 ) + ( rand()%( Display->w / 320 ) )  );
    yVel = ( Display->w / 320 );

}

void Ball::render()
{
    //Show the dot
    apply_surface( hit_box.x, hit_box.y, Surf_Sprite_Sheet, Display, &clip_ball );
}

//void Ball::resize(){
