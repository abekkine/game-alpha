#ifndef EFFECT_MANAGER_H
#define EFFECT_MANAGER_H

#include <vector>

#include <particle.h>

class EffectManager
{
    private:
        static EffectManager* _instance;
        EffectManager();
        
    public:
        static EffectManager* Instance();
        ~EffectManager();
        void Render();
        int Explode(double x, double y);

    private:
        int _effect_count;
        std::vector<Particle *> _particles;
};

#endif

