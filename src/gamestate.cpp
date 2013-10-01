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

