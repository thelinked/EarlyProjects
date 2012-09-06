#ifndef SPLASH_H
#define SPLASH_H
using namespace std;

//This class isn't really needed. Everything could have been done in main but I'm trying new stuff like alpha blending between two surfaces and animation so I kept it seperate.
class Menu
{
    private:

    //Surfaces
    //-----------------------------------
    SDL_Surface *Surf_Logo_Sprite; //Used for holding the sprites
    SDL_Surface *Surf_Menu_Sprite; //Used for holding the sprites

    SDL_Surface *Surf_Menu_Black;   //Used for the splash Screen
    SDL_Surface *Surf_Menu_White;


    SDL_Event event;

    int alpha;
    int cursor;
    int screen;

    int menu_offsetX;
    int menu_offsetY;
    int menu_offsetX_cursor;
    int menu_offsetY_cursor;

    public:

    //Surfaces
    //-----------------------------------
    SDL_Surface* Display;

    //Rect array for holding positions for the sprites
    //-----------------------------------
    SDL_Rect rect_menu_logo[12];
    SDL_Rect rect_menu[2];


    Menu();
    int get_screen();
    void logo();
    void fade( std::string color );
    void render();
    void handle_event( SDL_Event );
    void show_instructions();
    bool load_files();
    void clean_up();
};


#endif //SPLASH_H
