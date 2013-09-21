#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <vector>

#include <enemy.h>

class EnemyManager 
{
    public:
        EnemyManager();
        ~EnemyManager();
        void Init();
        void Render();

    private:
        void Defaults();

    private:
        std::vector<Enemy *> _enemies;
};

#endif

