#ifndef ENEMY_H
#define ENEMY_H

#include <object.h>
#include <bullet.h>

class Enemy : public Object
{
    public:
        Enemy(double x, double y);
        ~Enemy();
        Bullet* Fire();
        void Render();
        bool Alive();
        int Group();
        void Group(int group);
        bool CollisionWith(Object* object);
        Vector2 const& Position();
        double Size();

    private:
        double _vx;
        double _vy;
        double _alpha;
        double _span;
        double _reload_max;
        double _reload_delta; 
        double _reload_value;
};

#endif

