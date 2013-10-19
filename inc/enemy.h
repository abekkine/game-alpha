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
        void Update(double timestep);
        bool CollisionWith(Object* object);

    private:
        Vector2d _velocity;
        double _alpha;
        double _reload_max;
        double _reload_value;
        double _width;
        double _height;
        double _c1;
        double _c2;
        double _c3;
        double _c4;
};

#endif

