#ifndef GALAXY_H
#define GALAXY_H

#include <definitions.h>
#include <layer.h>
#include <event.h>
#include <player.h>
#include <enemymanager.h>
#include <obstaclemanager.h>

class Foreground : public Layer
{
    private:
        enum MoveType {
            move_NONE = 0,
            move_LEFT,
            move_RIGHT,
            move_UP,
            move_DOWN
        };

    public:
        Foreground();
        ~Foreground();
        bool Init( Volume& viewport );
        void Render();
        void Toggle();
        void ToggleWireframe();
        void ProcessCommand( Event::CommandType cmdCode );
        double PlayerHealth();

    private:
        // Methods.
        void Defaults();
        void RenderForegroundLayer();

        void RenderGround();
        void RenderPlayer();
        void RenderScore();

    private:
        // Member.
        bool _visible;
        bool _wireframe;

        MoveType _move_horizontal;
        Player* _player;
        EnemyManager* _enemyMgr;
        ObstacleManager* _obstacleMgr;
};

#endif
