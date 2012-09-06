#ifndef TIMER_H
#define TIMER_H
using namespace std;

class Timer
{
    private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //Stores the desired framerate
    int frames_per_second;

    //The timer status
    bool paused;
    bool started;

    public:
    //Initializes variables
    Timer( int FRAMES_PER_SECOND = 60 );

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();
    void frame_cap();

    //Gets the timer's time
    int get_ticks();

    //Checks the status of the timer
    bool is_started();
    bool is_paused();
};


#endif //TIMER_H
