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
    _width = Config::Instance()->enemy_width;
    _height = Config::Instance()->enemy_height;
    _size = (_width+_height)*0.5;
    _group = Object::grpENEMY;
    _type = objEnemy;
    _velocity = Vector2d(0.0, 0.0);
    _alpha = 0.0;
    _reload_max = Config::Instance()->enemy_reload_time;
    _reload_value = Util::Instance()->RandomValue(0.0, _reload_max);
    _score_value = 100;
    _player_hit = false;

    _c1 = Config::Instance()->enemy_c1;
    _c2 = Config::Instance()->enemy_c2;
    _c3 = Config::Instance()->enemy_c3;
    _c4 = Config::Instance()->enemy_c4;
}

Enemy::~Enemy()
{
}

void Enemy::Render()
{
    if( _visible )
    {
        glPushMatrix();
        glLoadIdentity();
        glTranslated( _position.x, _position.y, 0.0 );

        glColor3d(1.0, 1.0, 1.0);
        glBegin( GL_QUADS );
        glVertex2d( -_width, -_height );
        glVertex2d( -_width,  _height );
        glVertex2d(  _width,  _height );
        glVertex2d(  _width, -_height );
        glEnd();
        glPopMatrix();
    }
}

void Enemy::Update(double timestep)
{
    const double PATROL_SPEED = 1.0;

    // Movement
    _alpha += PATROL_SPEED * timestep;
    _velocity.x = _c1 * cos(_alpha) * _c4;
    _velocity.y = _c2 * sin(_alpha * _c3) * _c4;

    _position.x += _velocity.x * timestep;
    _position.y += _velocity.y * timestep;

    // Fire
    if( _reload_value < _reload_max )
    {
        _reload_value += timestep;
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
    bullet->Group(Object::grpENEMY);
    bullet->Velocity(Vector2d(_velocity.x, -Config::Instance()->enemy_bullet_speed));

    return bullet;
}

bool Enemy::CollisionWith(Object* object)
{
    object = object;
    
    return false;
}
