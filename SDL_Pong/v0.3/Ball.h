#ifndef BALL_H
#define BALL_H
#include <vector>
#include <cmath>
using namespace std;

//A circle stucture
struct Circle
{
    int x, y;
    int r;
};

class Ball
{
    private:
    //The area of the dot
    Circle c;

    //Surfaces
    //-----------------------------------
    SDL_Surface* Surf_Sprite_Sheet;

    //This are used for storing details on the sprites used.
    //-----------------------------------
    SDL_Rect clip_ball;

    //Ball Varibles
    //-----------------------------------
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
    Ball( int );
    bool load_files();
    bool check_collision( SDL_Rect, SDL_Rect );
    int move( SDL_Rect, SDL_Rect );
    void render();
    void resize();
    void clean_up();
    void reset();
};


#endif BALL_H
