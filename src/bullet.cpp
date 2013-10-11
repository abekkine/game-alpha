#include <math.h>
#include <GL/gl.h>

#include <bullet.h>
#include <config.h>
#include <effectmanager.h>

Bullet::Bullet(double x, double y) :
 LIFE_MAX(1.0),
 LIFE_DELTA(0.001)
{
    _position.x = x;
    _position.y = y;
    _type = objBullet;
    _vx = 0.0;
    _vy = 0.0;
    _life = LIFE_MAX;
    _size = 0.003;
    _visible = true;
}

Bullet::~Bullet()
{
}

void Bullet::Velocity(double vx, double vy)
{
    _vx = vx;
    _vy = vy;
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

    _position.x += _vx;
    _position.y += _vy;

    if( _position.y < -0.4 ) {
        _life = LIFE_DELTA;
        EffectManager::Instance()->Explode(EffectManager::explosionGROUND, _position.x, _position.y);
    }

    _life -= LIFE_DELTA;
}

bool Bullet::CollisionWith(Object* object)
{
    bool collision = false;
    Vector2 objPos;
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

        EffectManager::Instance()->Explode(EffectManager::explosionAIR, _position.x, _position.y);
    }


    return collision;
}

