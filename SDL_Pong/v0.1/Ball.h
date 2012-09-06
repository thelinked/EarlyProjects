#ifndef BALL_H
#define BALL_H
using namespace std;

class Ball
{
    private:

    //Surfaces
    //-----------------------------------
    SDL_Surface* Surf_Sprite_Sheet;

    //This are used for storing details on the sprites used.
    //-----------------------------------
    SDL_Rect clip_ball;

    //Ball Varibles
    //-----------------------------------
    int screen_width;
    int screen_height;
    int ball_width;
    int ball_height;
    public:

    //Surfaces
    //-----------------------------------
    SDL_Surface* Display;

    //Collision box
    //-----------------------------------
    SDL_Rect hit_box;

    //The velocity of the Ball
    //-----------------------------------
    float xVel, yVel;

    //Ball Functions
    //-----------------------------------
    Ball( int, int );
    bool load_files();
    bool check_collision( SDL_Rect, SDL_Rect );
    int move( SDL_Rect, SDL_Rect );
    void render();
    void clean_up();
    void reset();
};


#endif BALL_H
