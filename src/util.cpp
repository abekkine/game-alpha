#include <stdlib.h>

#include <util.h>

Util* Util::_instance = 0;

Util* Util::Instance()
{
    if( _instance == 0 )
    {
        _instance = new Util();
    }

    return _instance;
}

Util::Util()
{
}

Util::~Util()
{
}

double Util::RandomValue(double min, double max)
{
    double r_value;

    r_value = (double) rand() / (double) RAND_MAX;
    r_value *= (max-min);
    r_value += min;

    return r_value;
}

