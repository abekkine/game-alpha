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
    _gamemanager = new GameManager();
    _display = new Display();

    GameState::Instance()->State(GameState::gsMENU);

    _gamemanager->Init();

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
    GameState* gamestate = GameState::Instance();
    puts("Application::Run()");

    while( gamestate->State() != GameState::gsQUIT )
    {
        Event::Instance()->Update();
        ProcessCommands();
        _num_ticks = _timer->GetElapsed();
        if( _num_ticks > _ticks_period )
        {
            _timer->Reset();
            if( gamestate->State() != GameState::gsMENU ) {
                _gamemanager->Update( _time_step );
            }
        }

        _gamemanager->MovePlayer();

        _display->Render();
    }
}

void Application::ProcessCommands()
{
    Command* cmd;

    do {
        cmd = CommandManager::Instance()->Get();
        if( cmd != 0 )
        {
            _display->ProcessCommand( cmd );
            _gamemanager->ProcessCommand( cmd );
        }
    } while( cmd != 0 );
}
