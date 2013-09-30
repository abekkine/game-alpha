#include <stdio.h>

#include <objectmanager.h>
#include <effectmanager.h>

EffectManager* EffectManager::_instance = 0;

EffectManager* EffectManager::Instance()
{
    if( _instance == 0 )
    {
        _instance = new EffectManager();
    }

    return _instance;
}

EffectManager::EffectManager()
{
    _effect_count = 0;
}

EffectManager::~EffectManager()
{
}

int EffectManager::Explode(double x, double y)
{
    //DEBUG
    puts("EffectManager::Explode()");

    Particle* p = 0;

    _effect_count++;

    for(int i=0; i<20; i++)
    {
        p = new Particle(_effect_count, x, y);
        p->Randomize();
        _particles.push_back( p );
    }

    return _effect_count;
}

void EffectManager::Render()
{
    std::vector<Particle *>::iterator iParticle;

    for(iParticle=_particles.begin(); iParticle!=_particles.end(); ++iParticle)
    {
        if( (*iParticle)->Alive() )
        {
            (*iParticle)->Render();
        }
        else
        {
            delete (*iParticle);
            iParticle = _particles.erase( iParticle );
            if( iParticle == _particles.end() )
            {
                break;
            }
        }
    }
}

