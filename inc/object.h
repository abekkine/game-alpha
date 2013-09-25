#ifndef OBJECT_H
#define OBJECT_H

class Object
{
    public:
        virtual void Render() = 0;
        virtual bool Alive() = 0;

    protected:
        double _x;
        double _y;
};

#endif

