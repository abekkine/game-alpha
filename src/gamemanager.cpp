#include <gamestate.h>
#include <gamemanager.h>

GameManager::GameManager()
{
    _obstaclemanager = 0;
    _enemymanager = 0;
    _player = 0;
    _move_horizontal = move_NONE;
}

GameManager::~GameManager()
{
}

bool GameManager::Init()
{
    bool result = true;

    _objectmanager = ObjectManager::Instance();
    _effectmanager = EffectManager::Instance();

    // TODO : No magic numbers.
    _player = new Player( Vector2d(0.0, -0.36) );
    _objectmanager->Add( _player );

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

void GameManager::MovePlayer()
{
    switch( _move_horizontal ) {
        case move_LEFT:
            _player->MoveLeft();
            break;
        case move_RIGHT:
            _player->MoveRight();
            break;
        default:
            break;
    }
}

void GameManager::ProcessCommand(Command* cmd)
{
    Command::CommandType code;

    code = cmd->Code((int) GameState::Instance()->State());
    switch( code )
    {
        case Command::cmd_LEFT_ENABLE:
            _move_horizontal = move_LEFT; break;
        case Command::cmd_LEFT_DISABLE:
            _move_horizontal = move_NONE; break;
        case Command::cmd_RIGHT_ENABLE:
            _move_horizontal = move_RIGHT; break;
        case Command::cmd_RIGHT_DISABLE:
            _move_horizontal = move_NONE; break;

        case Command::cmd_FIRE:
            ObjectManager::Instance()->Add( _player->Fire() );
            break;    

        case Command::cmd_QUIT:
            GameState::Instance()->State(GameState::gsMENU);
            break;

        default:
            break;
    }
}
