#ifndef ENEMY_H
#define ENEMY_H

#include <object.h>
#include <bullet.h>

class Enemy : public Object
{
    public:
        Enemy(Vector2d position);
        ~Enemy();
        Bullet* Fire();
        void Render();
        void Update();
        bool CollisionWith(Object* object);

    private:
        Vector2d _velocity;
        double _alpha;
        double _span;
        double _reload_max;
        double _reload_delta; 
        double _reload_value;
};

#endif

