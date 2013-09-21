#include <enemymanager.h>

EnemyManager::EnemyManager()
{
    Defaults();
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Defaults()
{
    _enemies.clear();
}

void EnemyManager::Init()
{
    Enemy* anEnemy;

    for(double ix=-0.7; ix<=0.7; ix+=0.1)
    {
        for(double iy=0.3; iy>=0.0; iy-=0.1)
        {
            anEnemy = new Enemy(ix, iy);
            _enemies.push_back( anEnemy );
        }
    }
}

void EnemyManager::Render()
{
    Enemy* iEnemy;
    std::vector< Enemy* >::iterator iter;

    for(iter=_enemies.begin(); iter!=_enemies.end(); ++iter)
    {
        iEnemy = *iter;
        iEnemy->Render();
    }
}

