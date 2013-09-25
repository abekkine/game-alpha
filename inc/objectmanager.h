#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <vector>

#include <object.h>

class ObjectManager
{
    private:
        static ObjectManager* _instance;
        ObjectManager();

    public:
        static ObjectManager* Instance();
        ~ObjectManager();
        void Render();
        void Add(Object* object);

    private:
        std::vector<Object *> _objects;
};

#endif
