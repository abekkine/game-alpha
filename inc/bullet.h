#ifndef BULLET_H
#define BULLET_H

#include <object.h>

class Bullet : public Object
{
    public:
        Bullet(double x, double y);
        ~Bullet();
        void Owner(int owner);
        void Velocity(double vx, double vy);
        void Render();

    private:
        int _owner;
        double _vx;
        double _vy;
};

#endif

