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
        _a[i] = i * M_PI / 2.0;
        printf("%f %f\n", _r[i], _a[i]);
    }
}

void Obstacle::Render()
{
    glPushMatrix();
    glLoadIdentity();
    glTranslated( _x, _y, 0.0 );
    
    glColor3d(1.0, 0.0, 0.0);
    glBegin( GL_LINE_LOOP );
    for(int i=0; i<4; i++)
    {
        glVertex2d( _r[i] * cos(_a[i]), _r[i] * sin(_a[i]) );
    }
    glEnd();
    glPopMatrix();
}

void Obstacle::Randomize(double r, double a)
{
    r = r;
    a = a;
}

