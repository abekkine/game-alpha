#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <objectmanager.h>
#include <enemymanager.h>
#include <obstaclemanager.h>
#include <effectmanager.h>
#include <command.h>

class GameManager
{
    public:
        GameManager();
        ~GameManager();
        bool Init();
        void Update(double timestep);
        void ProcessCommand( Command* cmd );
        void Reset();

    private:
        ObjectManager* _objectmanager;
        EffectManager* _effectmanager;
        EnemyManager* _enemymanager;
        ObstacleManager* _obstaclemanager;
};

#endif

