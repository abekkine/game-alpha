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
        virtual void Render() = 0;
        virtual bool CollisionWith(Object* object) = 0;

    public:
        bool Alive();
        int Group();
        void Group(int group);
        double Size();
        Vector2 const& Position();
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
        Vector2 _position;
        double _size;
        int _group;
        double _life;
        bool _visible;
};

#endif

