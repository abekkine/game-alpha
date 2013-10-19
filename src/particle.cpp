#include <stdio.h>
#include <math.h>
#include <GL/gl.h>

#include <particle.h>
#include <util.h>

Particle::Particle(int id, Vector2d position)
{
    _effect_id = id;
    _position = position;
    _score_value = 0;
    _player_hit = false;

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
    _group = Object::grpNONE;
}

void Particle::Randomize( spreadType spread )
{
    const double MAX_PARTICLE_SPEED = 1.0;
    // Direction between 0..360.
    double dir;
    // Speed between 0.0 .. 0.005.
    double speed = Util::Instance()->RandomValue( 0.0, MAX_PARTICLE_SPEED );

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

void Particle::Update(double timestep)
{
    const double FADE_RATE = 1.0;

    _life -= FADE_RATE * timestep;
    _position.x += _velocity.x * timestep;
    _position.y += _velocity.y * timestep;
}

bool Particle::CollisionWith(Object* object)
{
    object = object;

    return false;
}

