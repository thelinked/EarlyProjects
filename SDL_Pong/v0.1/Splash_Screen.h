#ifndef SPLASH_H
#define SPLASH_H
using namespace std;

//This class isn't really needed. Everything could have been done in main but I'm trying new stuff like alpha blending between two surfaces and animation so I kept it seperate.
class Splash_Screen
{
    private:

    //Surfaces
    //-----------------------------------
    SDL_Surface *Surf_Splash_Front;   //Used for the splash Screen
    SDL_Surface *Surf_Splash_Sprite; //Used for holding the sprites

    int screen_width;
    int screen_height;
    int alpha;
    int offsetX;
    int offsetY;

    public:

    //Surfaces
    //-----------------------------------
    SDL_Surface* Display;


    //Collision box
    //-----------------------------------
    SDL_Rect rect_splash_screen[12];

    Splash_Screen( int, int );
    void logo();
    void fade();
   // void show_instructions( SDL_Event );
    bool load_files();
    void clean_up();
};


#endif SPLASH_H
