#ifndef PARTICLE_H
#define PARTICLE_H

#include <object.h>

class Particle : public Object
{
    public:
        typedef enum {
            stALL = 0,
            stUP
        } spreadType;

    public:
        Particle(int id, Vector2d position);
        ~Particle();
        void Render();
        void Update(double timestep);
        bool CollisionWith(Object* object);
        void Randomize( spreadType spread=stALL );

    private:
        void Defaults();

    private:
        int _effect_id;
        Vector2d _velocity;
};

#endif
