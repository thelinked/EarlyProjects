#ifndef TABLE_H
#define TABLE_H
using namespace std;

//The table

class Table
{
    private:

    //Table Varibles
    //-----------------------------------
    char grid[3][3];
    int cell_width;
    int cell_height;
    int screen_width;
    int screen_height;
    int screen_bpp;
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

    //Tables Functions
    //-----------------------------------
    Table( int, int, int, int, int );
    bool init();
    bool update_screen();
    bool load_files();
    bool handle_event();
    void apply_surface( int, int, SDL_Surface*, SDL_Surface*, SDL_Rect*);
    void set_clips();
    void clean_up();
    void show_backround();
    void check_win();
    void win();
    void restart();

};


#endif TABLE_H
