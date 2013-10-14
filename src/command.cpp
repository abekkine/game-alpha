#include <command.h>

CommandManager* CommandManager::_instance = 0;

CommandManager* CommandManager::Instance()
{
    if( _instance == 0 )
    {
        _instance = new CommandManager();
    }

    return _instance;
}

CommandManager::CommandManager()
{
}

CommandManager::~CommandManager()
{
}

Command* CommandManager::Get()
{
    Command* cmd = 0;

    if( !_command_queue.empty() )
    {
        cmd = _command_queue.front();
        _command_queue.pop();
    }

    return cmd;
}

void CommandManager::Push( Command* cmd )
{
    if( cmd != 0 )
    {
        _command_queue.push( cmd );
    }
}

