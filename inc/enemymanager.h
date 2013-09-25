#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <enemy.h>

class EnemyManager 
{
    public:
        EnemyManager();
        ~EnemyManager();
        void Init();

    private:
        void Defaults();
};

#endif

