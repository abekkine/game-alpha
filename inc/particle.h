#ifndef PARTICLE_H
#define PARTICLE_H

#include <object.h>

class Particle : public Object
{
    public:
        Particle(int id, double x, double y);
        ~Particle();
        void Render();
        bool CollisionWith(Object* object);
        void Randomize();

    private:
        void Defaults();

    private:
        int _effect_id;
        double _vx;
        double _vy;
};

#endif
