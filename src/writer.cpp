#include <config.h>
#include <writer.h>

Writer* Writer::_instance = 0;

Writer* Writer::Instance()
{
    if( _instance == 0 )
    {
        _instance = new Writer();
    }
    
    return _instance;
}

Writer::Writer()
{
    puts("Writer::Writer()");

    Defaults();
}

Writer::~Writer()
{
    MessageDisplayType* p_message;
    std::vector< MessageDisplayType* >::iterator iter;

    puts("Writer::~Writer()");

    for( iter = _message_list.begin(); iter != _message_list.end(); ++iter )
    {
        p_message = *iter;
        delete p_message;
    }

    delete _font;
}

void Writer::Defaults()
{
    _font = 0;
    _message_list.clear();
    // TODO : Font value should be obtained from _font instance.
    _font_height = Config::Instance()->font_size;

    _cursor.x = 8;
    _cursor.y = _font_height;
}

bool Writer::Init()
{
    bool result = false;

    _font = new Font();
    
    result = _font->Init();

//DEBUG
    printf( "_font_height(%d)\n", _font_height );
//END
    
    return result;
}

void Writer::SetColor( double* color ) {

    if( _font != 0 ) {
        _font->SetColor( color );
    }
}

void Writer::UpdateOrigin( Vector2i& p )
{
    _origin = p;
}

void Writer::Add( std::string text )
{
    MessageDisplayType* new_message = new MessageDisplayType;

    new_message->x = _cursor.x;
    new_message->y = _cursor.y;
    new_message->type = MSG_TEXT_ONLY;
    new_message->format = text;
    new_message->value = 0;

    _message_list.push_back( new_message );

    _cursor.y += _font_height;
}

void Writer::Add( std::string format, int* value )
{
    MessageDisplayType* new_message = new MessageDisplayType;

    new_message->x = _cursor.x;
    new_message->y = _cursor.y;
    new_message->type = MSG_INTEGER;
    new_message->format = format;
    new_message->value = (void *) value;

    _message_list.push_back( new_message );

    _cursor.y += _font_height;
}

void Writer::Add( std::string format, double* value )
{
    MessageDisplayType* new_message = new MessageDisplayType;

    new_message->x = _cursor.x;
    new_message->y = _cursor.y;
    new_message->type = MSG_DOUBLE;
    new_message->format = format;
    new_message->value = (void *) value;

    _message_list.push_back( new_message );

    _cursor.y += _font_height;
}

void Writer::Render()
{
    MessageDisplayType* p_message;
    std::vector< MessageDisplayType* >::iterator iter;

    for( iter = _message_list.begin(); iter != _message_list.end(); ++iter )
    {
        p_message = *iter;
        memset(_text_buffer, 0, BUFFER_SIZE);
        switch( p_message->type ) {
            case MSG_TEXT_ONLY:
                strcpy( _text_buffer, p_message->format.c_str() );
                break;

            case MSG_INTEGER:
                sprintf( _text_buffer, p_message->format.c_str(), *((int *) p_message->value) );
                break;

            case MSG_DOUBLE:
                sprintf( _text_buffer, p_message->format.c_str(), *((double *) p_message->value) );
                break;
        }

        _font->Print( _origin.x + p_message->x, _origin.y + p_message->y, std::string(_text_buffer) );
    }
}

