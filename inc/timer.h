#ifndef TIMER_H
#define TIMER_H

#include <omp.h>

class Timer
{
    public:
        Timer();
        ~Timer();
        void Reset();
        double GetElapsed();
        double GetFPS();

    private:
        // Methods
        double CurrentTime();
        void Defaults();

    private:
        // Members
        double _currentTime;
        double _prevTime;
        double _startTime;
        double _fps;
        int _frame_count;
};

#endif

