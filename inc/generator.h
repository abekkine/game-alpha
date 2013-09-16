#ifndef GENERATOR_H
#define GENERATOR_H

#include <libnoise/noise.h>
#include <vector.h>

class Generator
{
    public:
        Generator();
        ~Generator();

        double GetValue( Vector2d& p, double z );
        void SetOctaves( int n );
        void SetFrequency( double f );

    private:
        // Members
        noise::module::Perlin _noiseModule;
};

#endif

