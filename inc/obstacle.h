#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <object.h>

class Obstacle : public Object
{
    public:
        Obstacle(double x, double y, double r);
        ~Obstacle();
        void Render();
        bool Alive();
        bool CollisionWith(Object* object);
        int Group();
        void Group(int group);
        void Randomize(double r, double a);
        Vector2 const& Position();
        double Size();

    private:
        void Defaults();
        double RandomValue(double min, double max);

    private:
        double _r[4];
        double _a[4];
};

#endif
