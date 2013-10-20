#ifndef OBSTACLE_MANAGER_H
#define OBSTACLE_MANAGER_H

#include <obstacle.h>

class ObstacleManager
{
    public:
        ObstacleManager();
        ~ObstacleManager();
        bool Init();

    private:
        void Defaults();
        void CreateBlock(double x, double y, double w, double h, double d);
};

#endif
