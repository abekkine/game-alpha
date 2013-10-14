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

        Command(CommandType code, int page) {
            _code = code;
            _page = page;
        }

        CommandType Code(int page=-1) {

            CommandType value;
            if( page == _page ) {
                value = _code;
            } else {
                value = cmd_NONE;
            }
            return value;
        }

    private:
        CommandType _code;
        int _page;
};

class CommandManager
{
    private:
        static CommandManager* _instance;
        CommandManager();

    public:
        static CommandManager* Instance();
        ~CommandManager();
        Command* Get();
        void Push( Command* cmd );

    private:
        std::queue< Command* > _command_queue;
};

#endif


