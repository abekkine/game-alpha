#ifndef COMMAND_H
#define COMMAND_H

#include <queue>

class Command
{
    public:
        // Command Definitions.
        enum CommandType {
            cmd_NONE = 0,
            cmd_TOGGLE_WIREFRAME,
            cmd_TOGGLE_BACKGROUND,
            cmd_TOGGLE_FOREGROUND,
            cmd_TOGGLE_PANEL,
            cmd_ZOOM,
            cmd_PAN,
            cmd_SELECT,
            cmd_UP,
            cmd_DOWN,
            cmd_LEFT_ENABLE,
            cmd_LEFT_DISABLE,
            cmd_RIGHT_ENABLE,
            cmd_RIGHT_DISABLE,
            cmd_FIRE,
            cmd_QUIT
        };

    private:
        static Command* _instance;
        Command();

    public:
        static Command* Instance();
        ~Command();
        CommandType GetCommand();
        void PushCommand( CommandType code );

    private:
        std::queue< CommandType > _command_queue;

};

#endif


