#include <stdio.h>

#include <bulletmanager.h>

BulletManager* BulletManager::_instance = 0;

BulletManager* BulletManager::Instance()
{
    if( _instance == 0 )
    {
        _instance = new BulletManager();
    }

    return _instance;
}

BulletManager::BulletManager()
{
    _bullets.clear();
}

BulletManager::~BulletManager()
{
}

void BulletManager::Render()
{
    std::vector<Bullet *>::iterator iter;
    Bullet* aBullet;

    for(iter=_bullets.begin(); iter!=_bullets.end(); ++iter)
    {
        aBullet = *iter;
        if( aBullet->Alive() )
        {
            aBullet->Render();
        }
        else
        {
            delete aBullet;
            iter = _bullets.erase( iter );
            if( iter == _bullets.end() ){
                break;
            }
        }
    }
}

void BulletManager::AddBullet( Bullet* bullet )
{
    _bullets.push_back( bullet );
}

