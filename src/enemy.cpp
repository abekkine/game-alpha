#include <GL/gl.h>
#include <math.h>

#include <enemy.h>
#include <config.h>
#include <util.h>
#include <objectmanager.h>

Enemy::Enemy(Vector2d position)
{
    _life = 1.0;
    _visible = true;
    _position = position;
    _size = 0.03;
    _group = 1;
    _type = objEnemy;
    _velocity = Vector2d(0.0, 0.0);
    _alpha = 0.0;
    _span = 0.02;
    _reload_max = 50.0;
    _reload_value = Util::Instance()->RandomValue(0.0, _reload_max);
    _reload_delta = 0.01;
}

Enemy::~Enemy()
{
}

void Enemy::Render()
{
    if( _visible )
    {
        const double w = 0.02;
        const double h = 0.02;
        glPushMatrix();
        glLoadIdentity();
        glTranslated( _position.x, _position.y, 0.0 );

        glColor3d(1.0, 1.0, 1.0);
        glBegin( GL_QUADS );
        glVertex2d( -w, -h );
        glVertex2d( -w,  h );
        glVertex2d(  w,  h );
        glVertex2d(  w, -h );
        glEnd();
        glPopMatrix();
    }
}

void Enemy::Update()
{
    // Movement
    _alpha += 0.01;
    _velocity.x = _span * sin(_alpha) * 0.01;
    _velocity.y = 0.005 * sin(_alpha * 4.0) * 0.01;

    _position.x += _velocity.x;
    _position.y += _velocity.y;

    // Fire
    if( _reload_value < _reload_max )
    {
        _reload_value += _reload_delta;
    }
    else
    {
        _reload_value = 0.0;
        ObjectManager::Instance()->Add( Fire() );
    }
}

Bullet* Enemy::Fire()
{
    Bullet* bullet = new Bullet(Vector2d(_position.x, _position.y-0.02));
    bullet->Group(1);
    bullet->Velocity(Vector2d(_velocity.x, -0.00075));

    return bullet;
}

bool Enemy::CollisionWith(Object* object)
{
    object = object;
    
    return false;
}
