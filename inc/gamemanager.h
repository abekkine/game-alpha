#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <player.h>
#include <objectmanager.h>
#include <enemymanager.h>
#include <obstaclemanager.h>
#include <effectmanager.h>
#include <command.h>

class GameManager
{
    private:
        enum MoveType {
            move_NONE = 0,
            move_LEFT,
            move_RIGHT,
            move_UP,
            move_DOWN
        };

    public:
        GameManager();
        ~GameManager();
        bool Init();
        void Update(double timestep);
        void ProcessCommand( Command* cmd );
        void Reset();
        void MovePlayer();

    private:
        ObjectManager* _objectmanager;
        EffectManager* _effectmanager;
        Player* _player;
        EnemyManager* _enemymanager;
        ObstacleManager* _obstaclemanager;
        MoveType _move_horizontal;
};

#endif

