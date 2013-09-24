#include <stdlib.h>
#include <GL/gl.h>
#include <math.h>

#include <obstacle.h>
#include <config.h>

Obstacle::Obstacle(double x, double y, double r)
{
    _x = x;
    _y = y;
    _radii = r;
    Defaults();
}

Obstacle::~Obstacle()
{
}

void Obstacle::Defaults()
{
    for(int i=0; i<4; i++)
    {
        _r[i] = _radii;
        _a[i] = 0.5 * i * M_PI + 0.25 * M_PI;
        printf("%f %f\n", _r[i], _a[i]);
    }
}

void Obstacle::Render()
{
    glPushMatrix();
    glLoadIdentity();
    glTranslated( _x, _y, 0.0 );
    
    glColor3d(0.7, 0.7, 0.7);
//    glBegin( GL_LINE_LOOP );
    glBegin(GL_POLYGON);
    for(int i=0; i<4; i++)
    {
        glVertex2d( _r[i] * cos(_a[i]), _r[i] * sin(_a[i]) );
    }
    glEnd();
    glPopMatrix();
}

double Obstacle::RandomValue(double min, double max)
{
    double r_value;

    r_value = (double) rand() / (double) RAND_MAX;
    r_value *= (max-min);
    r_value += min;

    return r_value;
}

void Obstacle::Randomize(double r, double a)
{
    double r_dev, a_dev;
    for(int i=0; i<4; i++)
    {
        r_dev = RandomValue( -r, r );
        a_dev = RandomValue( -a, a );
        _r[i] *= (1.0 + 0.01 * r_dev);
        _a[i] *= (1.0 + 0.01 * a_dev);
    }
}

