#include <command.h>

Command* Command::_instance = 0;

Command* Command::Instance()
{
    if( _instance == 0 )
    {
        _instance = new Command();
    }

    return _instance;
}

Command::Command()
{
}

Command::~Command()
{
}

Command::CommandType Command::GetCommand()
{
    CommandType command_code = cmd_NONE;

    if( !_command_queue.empty() )
    {
        command_code = _command_queue.front();
        _command_queue.pop();
    }

    return command_code;
}

void Command::PushCommand( CommandType code )
{
    if( code != cmd_NONE )
    {
        _command_queue.push( code );
    }
}

