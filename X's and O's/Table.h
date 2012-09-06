#ifndef TABLE_H
#define TABLE_H

using namespace std;

//The table

class Table
{
    private:

    //Surfaces
    SDL_Surface* Surf_Sprite_Sheet;

    //Table Varibles
    //-----------------------------------
    char grid[3][3];
    int cell_width;
    int cell_height;
    int screen_width;
    int screen_height;
    bool xturn;
    //-----------------------------------
    //These are used for storing details on the sprites used.
    //-----------------------------------
    SDL_Rect clip_backround;
    SDL_Rect clip_x;
    SDL_Rect clip_o;
    SDL_Rect clip_xwin;
    SDL_Rect clip_owin;
    SDL_Rect clip_restart;
    //-----------------------------------
    //The event structure
    SDL_Event event;

    public:

    //Surfaces
    SDL_Surface* Display;

    //Tables Functions
    //-----------------------------------
    Table( int, int, int, int );
    bool load_files();
    bool handle_event();
    bool check_win();
    bool check_stalemate();

    void show_backround();
    void win();
    void restart();
    void clean_up();

};


#endif TABLE_H
