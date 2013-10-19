#include <vector.h>
#include <object.h>

Object::~Object()
{
}

void Object::Group(GroupType group)
{
    _group = group;
}

Object::GroupType Object::Group()
{
    return _group;
}

double Object::Size()
{
    return _size;
}

Vector2d const& Object::Position()
{
    return _position;
}

bool Object::Alive()
{
    return (_life > 0.0);
}

void Object::AddDamage(double damage)
{
    // TODO : Effective damage should depend on armor, shield, and existing damage level.
    _life -= damage;
}

int Object::ScoreValue()
{
    int score_value = 0;

    if( _player_hit )
    {
        score_value = _score_value;
    }

    return score_value;
}

void Object::PlayerHit(bool flag)
{
    _player_hit = flag;
}

Object::ObjectType Object::Type()
{
    return _type;
}

