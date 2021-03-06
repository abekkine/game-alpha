#include <stdlib.h>
#include <GL/gl.h>
#include <math.h>

#include <obstacle.h>
#include <config.h>
#include <util.h>

Obstacle::Obstacle(double x, double y, double r)
{
    _life = 1.0;
    _visible = true;
    _position.x = x;
    _position.y = y;
    _type = objObstacle;
    _size = r;
    _group = Object::grpOBSTACLE;
    _score_value = 10;
    _player_hit = false;
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
    }
}

void Obstacle::Render()
{
    if( _visible ) {
        glPushMatrix();
        glLoadIdentity();
        glTranslated( _position.x, _position.y, 0.0 );
    
        glColor4d(0.7, 0.7, 0.7, _life/1.0);
        glBegin(GL_POLYGON);
        for(int i=0; i<4; i++)
        {
            // TODO : avoid these calculations at render time.
            glVertex2d( _r[i] * cos(_a[i]), _r[i] * sin(_a[i]) );
        }
        glEnd();
        glPopMatrix();
    }
}

void Obstacle::Update(double timestep)
{
    timestep = timestep;
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

bool Obstacle::CollisionWith(Object* object)
{
    object = object;

    return false;
}
