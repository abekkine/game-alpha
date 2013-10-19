#include <stdio.h>
#include <math.h>
#include <GL/gl.h>

#include <particle.h>
#include <util.h>

Particle::Particle(int id, Vector2d position)
{
    _effect_id = id;
    _position = position;

    Defaults();
}

Particle::~Particle()
{
}

void Particle::Defaults()
{
    _life = 1.0;
    _visible = true;
    _type = objEffect;
    _size = 0.0;
    _group = 3;
}

void Particle::Randomize( spreadType spread )
{
    // Direction between 0..360.
    double dir;
    // Speed between 0.0 .. 0.005.
    double speed = Util::Instance()->RandomValue( 0.0, 0.005 );

    switch( spread )
    {
        case stALL:
            dir = Util::Instance()->RandomValue( 0.0, 2*M_PI );
            break;

        case stUP:
            dir = Util::Instance()->RandomValue( 0.0, M_PI );
            break;

        default:
            break;
    }

    _velocity.x = speed * cos( dir );
    _velocity.y = speed * sin( dir );
}

void Particle::Render()
{
    if( _visible )
    {
        glPushMatrix();
        glLoadIdentity();
        glTranslated(_position.x, _position.y, 0.0);
        glColor4d(1.0, 1.0, 1.0, _life/1.0);
        glPointSize(2.0);
        glBegin( GL_POINTS );
        glVertex2d( 0.0, 0.0 );
        glEnd();
        glPopMatrix();
    }
}

void Particle::Update()
{
    _life -= 0.005;
    _position.x += _velocity.x;
    _position.y += _velocity.y;
}

bool Particle::CollisionWith(Object* object)
{
    object = object;

    return false;
}

