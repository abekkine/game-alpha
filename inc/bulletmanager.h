#ifndef BULLET_MANAGER_H
#define BULLET_MANAGER_H

#include <vector>

#include <bullet.h>

class BulletManager
{
    private:
        static BulletManager* _instance;
        BulletManager();

    public:
        static BulletManager* Instance();
        ~BulletManager();

    public:
        void Render();
        void AddBullet( Bullet* bullet );

    private:
        std::vector<Bullet *> _bullets;
};

#endif

