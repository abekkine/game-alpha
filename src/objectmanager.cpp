#include <stdio.h>

#include <objectmanager.h>

ObjectManager* ObjectManager::_instance = 0;

ObjectManager* ObjectManager::Instance()
{
    if( _instance == 0 )
    {
        _instance = new ObjectManager();
    }

    return _instance;
}

ObjectManager::ObjectManager()
{
    _objects.clear();
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Render()
{
    std::vector<Object *>::iterator iObject;

    for(iObject=_objects.begin(); iObject!=_objects.end(); ++iObject)
    {
        if( (*iObject)->Alive() )
        {
            CheckCollision( *iObject );
            // TODO : Render & Update should be in separate timing frames.
            (*iObject)->Render();
            (*iObject)->Update();
        }
        else
        {
            delete (*iObject);
            iObject = _objects.erase( iObject );
            if( iObject == _objects.end() )
            {
                break;
            }
        }
    }
}

void ObjectManager::Add(Object* object)
{
    _objects.push_back( object );
}

void ObjectManager::CheckCollision(Object* object)
{
    std::vector<Object *>::iterator iObject;

    for(iObject=_objects.begin(); iObject!=_objects.end(); ++iObject)
    {
        if( object != *iObject )
        {
            object->CollisionWith(*iObject);
        }
    }
}


