#include <stdio.h>

#include <timer.h>

Timer::Timer()
{
    puts("Timer::Timer()");

    Defaults();
    Reset();
}

Timer::~Timer()
{
    puts("Timer::~Timer()");
}

void Timer::Defaults()
{
    _currentTime = omp_get_wtime();
    _prevTime = _currentTime;
    _startTime = _currentTime;
    _fps = 0.0;
    _frame_count = 0;
}

double Timer::CurrentTime()
{
    _currentTime = omp_get_wtime();

    return _currentTime;
}

void Timer::Reset()
{
    _startTime = CurrentTime();
}

double Timer::GetElapsed()
{
    return CurrentTime() - _startTime;
}

double Timer::GetFPS()
{
    double delta_time;

    CurrentTime();

    delta_time = _currentTime - _prevTime;
#ifdef METHOD_A
    _prevTime = _currentTime;
   
    if( delta_time > 0.0 ) {
        _fps = 1.0 / delta_time;
    } else {
        _fps = 0.0;
    } 
#else
    if( delta_time < 1.0 ) {
        _frame_count++;
    } else {
        _fps = _frame_count;
        _frame_count = 0;
        _prevTime = _currentTime;
    }
#endif

    return _fps;
}
