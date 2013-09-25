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
            (*iObject)->Render();
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


