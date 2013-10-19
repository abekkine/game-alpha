#include <math.h>
#include <GL/gl.h>

#include <vector.h>
#include <bullet.h>
#include <config.h>
#include <effectmanager.h>

Bullet::Bullet(Vector2d position) 
: EPSILON(1e-6)
{
    _position = position;
    _velocity = Vector2d(0.0, 0.0);

    _type = objBullet;

    _life = Config::Instance()->max_bullet_life;
    _life_delta = Config::Instance()->bullet_decay_rate;

    _width = Config::Instance()->bullet_width;
    _height = Config::Instance()->bullet_height;
    _size = (_width < _height) ? _width : _height; 
    _visible = true;

    _score_value = 500;
    _player_hit = false;
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
    if( _visible ) {

        glPushMatrix();
        glLoadIdentity();
        glTranslated(_position.x, _position.y, 0.0);

        glColor3d(0.8, 0.8, 0.8);

        glBegin(GL_QUADS);
        glVertex2d( -_width, -_height );
        glVertex2d( -_width,  _height );
        glVertex2d(  _width,  _height );
        glVertex2d(  _width, -_height );
        glEnd();

        glPopMatrix();
    }
}

void Bullet::Update(double timestep)
{
    _position.x += _velocity.x * timestep;
    _position.y += _velocity.y * timestep;

    if( _position.y < Config::Instance()->ground_level ) {
        _life = EPSILON;
        _player_hit = false;
        EffectManager::Instance()->Explode(EffectManager::explosionGROUND, _position);
    }

    _life -= _life_delta * timestep;
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
        // TODO : bullet damage should contain some random factor.
        object->AddDamage( Config::Instance()->bullet_damage );

        if( _group == Object::grpPLAYER || object->Type() == Object::objBullet )
        {
            object->PlayerHit( true );
        }
        else
        {
            object->PlayerHit( false );
        }

        _life = EPSILON;
        EffectManager::Instance()->Explode(EffectManager::explosionAIR, _position);
    }

    return collision;
}

