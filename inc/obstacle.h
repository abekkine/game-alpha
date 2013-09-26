#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <object.h>

class Obstacle : public Object
{
    public:
        Obstacle(double x, double y, double r);
        ~Obstacle();
        void Render();
        bool CollisionWith(Object* object);
        void Randomize(double r, double a);

    private:
        void Defaults();
        double RandomValue(double min, double max);

    private:
        double _r[4];
        double _a[4];
};

#endif
