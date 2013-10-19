#include <config.h>
#include <application.h>
#include <gamestate.h>
#include <objectmanager.h>
#include <effectmanager.h>

Application::Application()
{
    puts("Application::Application()");

    Defaults();
}

Application::~Application()
{
    puts("Application::~Application()");

    delete _display;
    delete _timer;
}

void Application::Defaults()
{
    puts("Application::Defaults()");

    _timer = 0;
    _display = 0;

    _ticks_period = -1.0;
    _time_step = -1.0;
    _quit_condition = false;
}

bool Application::Initialize()
{
    puts("Application::Initialize()");

    bool result = false;

    _timer = new Timer(); 
    _display = new Display();

    GameState::Instance()->State(GameState::gsMENU);

    result = _display->Init();
    if( result )
    {
        if( Config::Instance()->application_frequency > 0.0 )
        {
            _ticks_period = 1.0 / Config::Instance()->application_frequency;
        }
        else
        {
            _ticks_period = 0.0;
        }

        _timer->Reset();

        _time_step = Config::Instance()->application_timestep;
    }

    return result;
}

void Application::Run()
{
    ObjectManager* objectmanager = ObjectManager::Instance();
    EffectManager* effectmanager = EffectManager::Instance();
    GameState* gamestate = GameState::Instance();
    puts("Application::Run()");

    while( GameState::Instance()->State() != GameState::gsQUIT )
    {
        _num_ticks = _timer->GetElapsed();
        if( _num_ticks > _ticks_period )
        {
            _timer->Reset();
            if( gamestate->State() != GameState::gsMENU ) {
                objectmanager->Update( _time_step );
                effectmanager->Update( _time_step );
            }
        }

        _display->Render();
    }

    delete objectmanager;
    delete effectmanager;
}
