#ifndef APPLICATION_H
#define APPLICATION_H

#include <timer.h>
#include <display.h>
#include <gamemanager.h>

//! @brief Holds everything regarding the application.
class Application
{
    public:
        //! @brief Constructor.
        Application();
        //! @brief Destructor.
        ~Application();
        //! Startup initialization.
        bool Initialize();
        //! Main application loop.
        void Run();
        //! Process commands.
        void ProcessCommands();

    private:
        // Methods
        void Defaults();

    private:
        // Members
        Timer* _timer;
        Display* _display;
        GameManager* _gamemanager;

        float _ticks_period;
        float _time_step;
        float _num_ticks;
        bool _quit_condition;
};

#endif

