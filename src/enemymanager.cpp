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

bool EnemyManager::Init()
{
    bool result = true;
    Enemy* anEnemy;

    for(double ix=-0.7; ix<=0.7; ix+=0.1)
    {
        for(double iy=0.3; iy>=0.0; iy-=0.1)
        {
            anEnemy = new Enemy(Vector2d(ix, iy));
            ObjectManager::Instance()->Add( anEnemy );
        }
    }

    return result;
}

