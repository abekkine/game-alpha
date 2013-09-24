#include <GL/gl.h>
#include <math.h>

#include <enemy.h>
#include <config.h>
#include <util.h>
#include <bulletmanager.h>

Enemy::Enemy(double x, double y)
{
    _x = x;
    _y = y;
    _vx = 0.0;
    _vy = 0.0;
    _alpha = 0.0;
    _span = 0.02;
    _reload_max = 250.0;
    _reload_value = Util::Instance()->RandomValue(0.0, _reload_max);
    _reload_delta = 0.01;
}

Enemy::~Enemy()
{
}

void Enemy::Render()
{
    const double w = 0.02;
    const double h = 0.02;
    glPushMatrix();
    glLoadIdentity();
    glTranslated( _x, _y, 0.0 );

    glColor3d(1.0, 1.0, 1.0);
    glBegin( GL_QUADS );
    glVertex2d( -w, -h );
    glVertex2d( -w,  h );
    glVertex2d(  w,  h );
    glVertex2d(  w, -h );
    glEnd();
    glPopMatrix();

    // Movement
    _alpha += 0.01;
    _vx = _span * sin(_alpha) * 0.01;
    _vy = 0.005 * sin(_alpha * 4.0) * 0.01;

    _x += _vx;
    _y += _vy;

    // Fire
    if( _reload_value < _reload_max )
    {
        _reload_value += _reload_delta;
    }
    else
    {
        _reload_value = 0.0;
        BulletManager::Instance()->AddBullet( Fire() );
    }
}

Bullet* Enemy::Fire()
{
    Bullet* bullet = new Bullet(_x, _y-0.02);
    
    bullet->Owner(1);
    bullet->Velocity(_vx, -0.00075);

    return bullet;
}

