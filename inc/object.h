#ifndef OBJECT_H
#define OBJECT_H

#include <vector.h>

class Object
{
    public:
        typedef enum {
            grpNONE = 0,
            grpPLAYER,
            grpENEMY,
            grpOBSTACLE
        } GroupType;

        typedef enum {
            objNone = 0,
            objPlayer,
            objEnemy,
            objObstacle,
            objBullet,
            objEffect
        } ObjectType;

    public:
        virtual ~Object() = 0;
        virtual void Render() = 0;
        virtual void Update(double timestep) = 0;
        virtual bool CollisionWith(Object* object) = 0;

    public:
        bool Alive();
        GroupType Group();
        void Group(GroupType group);
        double Size();
        Vector2d const& Position();
        void AddDamage(double damage);
        int ScoreValue();
        void PlayerHit(bool flag);
        ObjectType Type();

    protected:
        ObjectType _type;
        Vector2d _position;
        double _size;
        GroupType _group;
        double _life;
        bool _visible;
        int _score_value;
        bool _player_hit;
};

#endif

