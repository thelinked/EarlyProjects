#ifndef WINDOW_H
#define WINDOW_H
using namespace std;

class Window
{
    private:
    //Whether the window is windowed or not
    bool windowed;

    //Whether the window is fine
    bool windowOK;

    public:
    //Constructor
    Window();

    //Surfaces
    //-----------------------------------
    SDL_Surface* Display;

    //Handle window events
    void handle_event( SDL_Event event );

    //Turn fullscreen on/off
    void toggle_fullscreen();

    //Check if anything's wrong with the window
    bool error();
};

#endif WINDOW_H
