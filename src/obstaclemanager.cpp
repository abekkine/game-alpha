#include <obstaclemanager.h>

ObstacleManager::ObstacleManager()
{
    Defaults();
}

ObstacleManager::~ObstacleManager()
{
}

void ObstacleManager::Defaults()
{
    _obstacles.clear();
}

void ObstacleManager::Init()
{
    Obstacle* anObstacle;

    // X, Y, and Radius.
    anObstacle = new Obstacle( 0.0, 0.0, 0.01 );
    // %10.0 deviation for both radius and angle.
    anObstacle->Randomize( 10.0, 10.0 );
    _obstacles.push_back( anObstacle );
}

void ObstacleManager::Render()
{
    Obstacle* iObstacle;
    std::vector<Obstacle *>::iterator iter;

    for(iter=_obstacles.begin(); iter!=_obstacles.end(); ++iter)
    {
        iObstacle = *iter;
        iObstacle->Render();
    }
}

