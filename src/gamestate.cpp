#include <stdio.h>

#include <gamestate.h>

GameState* GameState::_instance = 0;

GameState* GameState::Instance()
{
    if( _instance == 0 )
    {
        _instance = new GameState();
    }

    return _instance;
}

void GameState::Dump()
{
    switch( _state )
    {
        case GameState::gsMENU:
            puts("[ gsMENU     ]"); break;
        case GameState::gsPLAY:
            puts("[ gsPLAY     ]"); break;
        case GameState::gsQUIT:
            puts("[ gsQUIT     ]"); break;
        case GameState::gsGAMEOVER:
            puts("[ gsGAMEOVER ]"); break;
        case GameState::gsPAUSE:
            puts("[ gsPAUSE    ]"); break;
    }
}

GameState::GameState()
{
    _state = gsMENU;
}

GameState::~GameState()
{
}

GameState::GameStateType GameState::State()
{
    return _state;
}

void GameState::State( GameStateType state )
{
    _state = state;
}

