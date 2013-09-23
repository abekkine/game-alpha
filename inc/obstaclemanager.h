#ifndef OBSTACLE_MANAGER_H
#define OBSTACLE_MANAGER_H

#include <vector>

#include <obstacle.h>

class ObstacleManager
{
    public:
        ObstacleManager();
        ~ObstacleManager();
        void Init();
        void Render();

    private:
        void Defaults();
        void CreateBlock(double x, double y, double w, double h, double d);

    private:
        std::vector<Obstacle *> _obstacles;
};

#endif
