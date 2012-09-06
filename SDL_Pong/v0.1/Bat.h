#ifndef BAT_H
#define BAT_H
using namespace std;

class Bat
{
    private:

    //Surfaces
    //-----------------------------------
    SDL_Surface* Surf_Sprite_Sheet;
    SDL_Surface* Surf_Message;


    //Bat Varibles
    //-----------------------------------
    int screen_width;
    int screen_height;
    int bat_width;
    int bat_height;
    bool Player1;

    //These are used for storing details on the sprites used.
    //-----------------------------------
    SDL_Rect clip_bat;

    public:

    //Surfaces
    //-----------------------------------
    SDL_Surface* Display;

    //Collision box
    //-----------------------------------
    SDL_Rect hit_box;

    //Tracks the velocity of the Ball and the players score
    //-----------------------------------
    float xVel, yVel;
    int score;

    //Tables Functions
    //-----------------------------------
    Bat( int, int, bool );
    bool load_files();
    void handle_event( SDL_Event );
    void sort_score();
    void move();
    void clean_up();
    void render();

};

#endif BAT_H
