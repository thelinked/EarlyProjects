#ifndef GAME_H
#define GAME_H

#include "SDL/SDL.h"
#include "Graphics.h"
#include "Timer.h"
#include "Ball.h"
#include "Bat.h"
#include "Menu.h"

class Game
{
    public:
        Game();
        //----------------------------------------------------------------------------------------------
        Window Window;
        Menu Menu;
        Bat Player_1( int, int, bool ), Player_2( int. int, bool );
        Ball Ball( int );
        Timer Fps( int );
        //-----------------------------
    protected:
    private:
};

#endif // GAME_H
