#ifndef BULLET_H
#define BULLET_H

#include <object.h>

class Bullet : public Object
{
    public:
        Bullet(Vector2d position);
        ~Bullet();
        void Velocity(Vector2d velocity);
        void Render();
        void Update(double timestep);
        bool CollisionWith(Object* object);

    private:
        const double EPSILON;
        double _life_delta;
        Vector2d _velocity;
        double _width;
        double _height;
};

#endif

