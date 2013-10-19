#include <math.h>
#include <GL/gl.h>

#include <vector.h>
#include <bullet.h>
#include <config.h>
#include <effectmanager.h>

Bullet::Bullet(Vector2d position) :
 LIFE_MAX(1.0),
 LIFE_DELTA(0.001)
{
    _position = position;
    _velocity = Vector2d(0.0, 0.0);

    _type = objBullet;
    _life = LIFE_MAX;
    _size = 0.003;
    _visible = true;
}

Bullet::~Bullet()
{
}

void Bullet::Velocity(Vector2d velocity)
{
    _velocity = velocity;
}

void Bullet::Render()
{
    const double w = 0.002;
    const double h = 0.005;

    if( _visible ) {

        glPushMatrix();
        glLoadIdentity();
        glTranslated(_position.x, _position.y, 0.0);

        glColor3d(0.8, 0.8, 0.8);

        glBegin(GL_QUADS);
        glVertex2d( -w, -h );
        glVertex2d( -w,  h );
        glVertex2d(  w,  h );
        glVertex2d(  w, -h );
        glEnd();

        glPopMatrix();
    }
}

void Bullet::Update()
{
    _position.x += _velocity.x;
    _position.y += _velocity.y;

    if( _position.y < -0.4 ) {
        _life = LIFE_DELTA;
        EffectManager::Instance()->Explode(EffectManager::explosionGROUND, _position);
    }

    _life -= LIFE_DELTA;
}

bool Bullet::CollisionWith(Object* object)
{
    bool collision = false;
    Vector2d objPos;
    double objSize;
    double dx, dy, dr;

    if( _group == object->Group() )
        return false;

    objPos = object->Position();
    objSize = object->Size();
    dx = _position.x - objPos.x;
    dy = _position.y - objPos.y;
    dr = sqrt( dx*dx + dy*dy );

    if(dr < (_size+objSize) ) {
        collision = true;
        _visible = false;
        object->AddDamage( 0.25 );
        _life = LIFE_DELTA;

        EffectManager::Instance()->Explode(EffectManager::explosionAIR, _position);
    }


    return collision;
}

