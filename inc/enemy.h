#ifndef ENEMY_H
#define ENEMY_H

#include <object.h>

class Enemy : public Object
{
    public:
        Enemy(double x, double y);
        ~Enemy();
        void Render();

    private:
        double _x0;
        double _y0;
        double _alpha;
        double _span;
};

#endif

