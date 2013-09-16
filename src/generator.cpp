#include <stdio.h>

#include <generator.h>

Generator::Generator()
{
    puts("Generator::Generator()");
}

Generator::~Generator()
{
    puts("Generator::~Generator()");
}

double Generator::GetValue( Vector2d& p, double z )
{
    return _noiseModule.GetValue( p.x, p.y, z );
}

void Generator::SetOctaves( int n )
{
    _noiseModule.SetOctaveCount( n );
}

void Generator::SetFrequency( double f ) {

    _noiseModule.SetFrequency( f );
}


