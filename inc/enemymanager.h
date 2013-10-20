#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <enemy.h>

class EnemyManager 
{
    public:
        EnemyManager();
        ~EnemyManager();
        bool Init();

    private:
        void Defaults();
};

#endif

