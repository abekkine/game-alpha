#include <object.h>

void Object::Group(int group)
{
    _group = group;
}

int Object::Group()
{
    return _group;
}

double Object::Size()
{
    return _size;
}

Vector2 const& Object::Position()
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

