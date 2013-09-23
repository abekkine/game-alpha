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

    private:
        std::vector<Obstacle *> _obstacles;
};

#endif
