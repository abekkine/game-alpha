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
    _life -= damage;
}

Object::ObjectType Object::Type()
{
    return _type;
}

