#include <gamestate.h>
#include <gamemanager.h>

GameManager::GameManager()
{
    _obstaclemanager = 0;
    _enemymanager = 0;
}

GameManager::~GameManager()
{
}

bool GameManager::Init()
{
    bool result = true;

    _objectmanager = ObjectManager::Instance();
    _effectmanager = EffectManager::Instance();

    _enemymanager = new EnemyManager();
    result &= _enemymanager->Init();

    _obstaclemanager = new ObstacleManager();
    result &= _obstaclemanager->Init();

    return result;
}

void GameManager::Update(double timestep)
{
    _objectmanager->Update( timestep );
    _effectmanager->Update( timestep );
}

void GameManager::Reset()
{
}

void GameManager::ProcessCommand(Command* cmd)
{
    Command::CommandType code;

    code = cmd->Code((int) GameState::Instance()->State());
    switch( code )
    {
        case Command::cmd_QUIT:
            GameState::Instance()->State(GameState::gsMENU);
            break;

        default:
            break;
    }
}
