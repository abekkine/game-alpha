#ifndef OBJECT_H
#define OBJECT_H

#include <vector.h>

class Object
{
    public:
        virtual ~Object() = 0;
        virtual void Render() = 0;
        virtual void Update() = 0;
        virtual bool CollisionWith(Object* object) = 0;

    public:
        bool Alive();
        int Group();
        void Group(int group);
        double Size();
        Vector2d const& Position();
        void AddDamage(double damage);

    protected:
        typedef enum {
            objNone = 0,
            objPlayer,
            objEnemy,
            objObstacle,
            objBullet,
            objEffect
        } ObjectType;
        
        ObjectType _type;
        Vector2d _position;
        double _size;
        int _group;
        double _life;
        bool _visible;
};

#endif

