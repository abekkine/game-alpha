#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <object.h>

class Obstacle : public Object
{
    public:
        Obstacle(double x, double y, double r);
        ~Obstacle();
        void Render();
        void Update(double timestep);
        bool CollisionWith(Object* object);
        void Randomize(double r, double a);

    private:
        void Defaults();

    private:
        double _r[4];
        double _a[4];
};

#endif
