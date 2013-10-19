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
    _score = 0;
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Update(double timestep)
{
    std::vector<Object *>::iterator iObject;

    for(iObject=_objects.begin(); iObject!=_objects.end(); ++iObject)
    {
        if( (*iObject)->Alive() )
        {
            CheckCollision( *iObject );
            (*iObject)->Update(timestep);
        }
        else
        {
            _score += (*iObject)->ScoreValue();
            // TODO : What if object is deleted while still in rendering?
            delete (*iObject);
            iObject = _objects.erase( iObject );
            if( iObject == _objects.end() )
            {
                break;
            }
        }
    }
}

void ObjectManager::Render()
{
    std::vector<Object *>::iterator iObject;

    for(iObject=_objects.begin(); iObject!=_objects.end(); ++iObject)
    {
        (*iObject)->Render();
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

int ObjectManager::Score()
{
    return _score;
}
