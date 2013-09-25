#include <objectmanager.h>
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
}

void EnemyManager::Init()
{
    Enemy* anEnemy;

    for(double ix=-0.7; ix<=0.7; ix+=0.1)
    {
        for(double iy=0.3; iy>=0.0; iy-=0.1)
        {
            anEnemy = new Enemy(ix, iy);
            ObjectManager::Instance()->Add( anEnemy );
        }
    }
}

