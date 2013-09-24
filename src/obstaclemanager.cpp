#include <stdio.h>

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
    // X, Y, Width, Height, Density
    CreateBlock(-0.5, -0.2, 0.1, 0.05, 5.0);
    CreateBlock(-0.25, -0.2, 0.1, 0.05, 5.0);
    CreateBlock(0.0, -0.2, 0.1, 0.05, 5.0);
    CreateBlock(0.25, -0.2, 0.1, 0.05, 5.0);
    CreateBlock(0.5, -0.2, 0.1, 0.05, 5.0);
}

void ObstacleManager::CreateBlock(double x, double y, double w, double h, double d)
{
    Obstacle* anObstacle;
    double x_begin = x - 0.5 * w;
    double x_end = x + 0.5 * w;
    double y_begin = y - 0.5 * h;
    double y_end = y + 0.5 * h;
    double step = (w < h) ? w/d : h/d;

    for(double ix=x_begin; ix<=x_end; ix+=step)
    {
        for(double iy=y_begin; iy<=y_end; iy+=step)
        {
            // X, Y, and Radius.
            anObstacle = new Obstacle(ix, iy, 0.85 * step);
            // %10.0 deviation for both radius and angle.
            anObstacle->Randomize(10.0, 10.0);
            _obstacles.push_back( anObstacle );
        }
    }
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

