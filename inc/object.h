#ifndef OBJECT_H
#define OBJECT_H

struct Vector2
{
    double x;
    double y;
};

class Object
{
    public:
        virtual Vector2 const& Position() = 0;
        virtual double Size() = 0;
        virtual void Render() = 0;
        virtual bool Alive() = 0;
        virtual int Group() = 0;
        virtual void Group(int group) = 0;
        virtual bool CollisionWith(Object* object) = 0;

    protected:
        typedef enum {
            objNone = 0,
            objPlayer,
            objEnemy,
            objObstacle,
            objBullet
        } ObjectType;
        
        ObjectType _type;
        Vector2 _position;
        double _size;
        int _group;
};

#endif

