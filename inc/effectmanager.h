#ifndef EFFECT_MANAGER_H
#define EFFECT_MANAGER_H

#include <vector>

#include <vector.h>
#include <particle.h>

class EffectManager
{
    public:
        typedef enum {
            explosionAIR = 1,
            explosionGROUND
        } explosionType;

    private:
        static EffectManager* _instance;
        EffectManager();
        
    public:
        static EffectManager* Instance();
        ~EffectManager();
        void Render();
        int Explode(explosionType type, Vector2d position);

    private:
        int _effect_count;
        std::vector<Particle *> _particles;
};

#endif

