#ifndef BAT_H
#define BAT_H
using namespace std;

class Bat
{
    private:

    //Surfaces
    //-----------------------------------
    SDL_Surface* Surf_Sprite_Sheet;
    SDL_Surface* Surf_Score_Sheet;


    //Bat Varibles
    //-----------------------------------
    int bat_width;
    int bat_height;
    bool Player1;
    SDLKey control_up;
    SDLKey control_down;
    //These are used for storing details on the sprites used.
    //-----------------------------------
    SDL_Rect clip_bat;
    SDL_Rect clip_font[10];

    public:

    //Surfaces
    //-----------------------------------
    SDL_Surface* Display;

    //Collision box
    //-----------------------------------
    SDL_Rect hit_box;

    //Tracks the velocity of the Ball and the players score
    //-----------------------------------
    int xVel, yVel;
    int score;

    //Tables Functions
    //-----------------------------------
    Bat( int, int, bool );
    bool load_files();
    void handle_event( SDL_Event );
    void move();
    void resize();
    void clean_up();
    void render();

};
#endif BAT_H
