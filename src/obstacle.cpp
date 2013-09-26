#include <stdlib.h>
#include <GL/gl.h>
#include <math.h>

#include <obstacle.h>
#include <config.h>
#include <util.h>

Obstacle::Obstacle(double x, double y, double r)
{
    _position.x = x;
    _position.y = y;
    _type = objObstacle;
    _size = r;
    _group = 2;
    Defaults();
}

Obstacle::~Obstacle()
{
}

void Obstacle::Defaults()
{
    for(int i=0; i<4; i++)
    {
        _r[i] = _size;
        _a[i] = 0.5 * i * M_PI + 0.25 * M_PI;
        printf("%f %f\n", _r[i], _a[i]);
    }
}

void Obstacle::Render()
{
    glPushMatrix();
    glLoadIdentity();
    glTranslated( _position.x, _position.y, 0.0 );
    
    glColor3d(0.7, 0.7, 0.7);
    glBegin(GL_POLYGON);
    for(int i=0; i<4; i++)
    {
        glVertex2d( _r[i] * cos(_a[i]), _r[i] * sin(_a[i]) );
    }
    glEnd();
    glPopMatrix();
}

void Obstacle::Randomize(double r, double a)
{
    double r_dev, a_dev;
    for(int i=0; i<4; i++)
    {
        r_dev = Util::Instance()->RandomValue( -r, r );
        a_dev = Util::Instance()->RandomValue( -a, a );
        _r[i] *= (1.0 + 0.01 * r_dev);
        _a[i] *= (1.0 + 0.01 * a_dev);
    }
}

bool Obstacle::Alive()
{
    // TODO : implement
    return true;
}

bool Obstacle::CollisionWith(Object* object)
{
    object = object;

    return false;
}

