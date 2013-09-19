#include <vector.h>
#include <config.h>
#include <event.h>
#include <panel.h>
#include <writer.h>

Event* Event::_instance = 0;

int Event::_zoom_delta = 0;
Vector2i Event::_pan_delta(0, 0);

bool Event::_quit_condition = false;

Event* Event::Instance()
{
    if( _instance == 0 )
    {
        _instance = new Event();
    }

    return _instance;
}

Event::Event()
{
    puts("Event::Event()");

    Defaults();
    Init();
}

Event::~Event()
{
    puts("Event::~Event()");
}

void Event::Defaults()
{
    _mouse.x = 0;
    _mouse.y = 0;

    _pan_mode = false;
    _zoom_mode = false;
    _pan_start.x = 0;
    _pan_start.y = 0;
    _zoom_start.x = 0;
    _zoom_start.y = 0;
    _zoom_total = 0;

    _speed_factor = Config::Instance()->speed_factor_min;

    Writer::Instance()->Add("_speed_factor(%d)", &_speed_factor );
    Writer::Instance()->Add("zoom_delta(%d)", &Event::_zoom_delta );
    Writer::Instance()->Add("pan_dx(%d)", &Event::_pan_delta.x );
    Writer::Instance()->Add("pan_dy(%d)", &Event::_pan_delta.y );
}

bool Event::Init()
{
    bool result = true;

    return result;
}

bool Event::Update()
{
    bool result = true;
    
    Poll();

    CommandProcess();

    return result;
}

void Event::PanMode( bool value )
{
    _pan_mode = value;
}

void Event::PanUpdate()
{
    if( _pan_mode )
    {
        _zoom_delta = 0;
        _pan_delta.x = (_mouse.x - _pan_start.x) * _speed_factor;
        _pan_delta.y = (_mouse.y - _pan_start.y) * _speed_factor;

        PushCommand( cmd_PAN );

        _pan_start = _mouse;
    }
}

void Event::ZoomMode( bool value )
{
    _zoom_mode = value;
}

void Event::ZoomUpdate()
{
    if( _zoom_mode )
    {
        _zoom_delta = (_mouse.y - _zoom_start.y) * _speed_factor;
        _pan_delta.x = 0;
        _pan_delta.y = 0;

        LimitZoom();

        PushCommand( cmd_ZOOM );

        _zoom_start = _mouse;
    }
}


void Event::WheelZoom( SDL_MouseButtonEvent& button ) {

    switch( button.button ) {
        case SDL_BUTTON_WHEELDOWN:
            _zoom_delta = Config::Instance()->wheel_step * _speed_factor;
            break;

        case SDL_BUTTON_WHEELUP:
            _zoom_delta = -Config::Instance()->wheel_step * _speed_factor;
            break;
    }

    LimitZoom();
    _pan_delta.x = 0;
    _pan_delta.y = 0;
    PushCommand( cmd_ZOOM );
}

void Event::LimitZoom()
{
    if( _zoom_delta > 0 ) {
        if( (_zoom_total + _zoom_delta) >= Config::Instance()->zoom_limit_max ) {
            _zoom_delta = Config::Instance()->zoom_limit_max - _zoom_total;
        }
    } else if( _zoom_delta < 0 ) {
        if( (_zoom_total + _zoom_delta) <= Config::Instance()->zoom_limit_min ) {
            _zoom_delta = Config::Instance()->zoom_limit_min - _zoom_total;
        }
    }

    _zoom_total += _zoom_delta;
}

void Event::CommandProcess()
{
    int event_code = PopEvent();
   
    switch( event_code )
    {
        case evt_RIGHTBUTTON_PRESSED:
            PanMode( true );
            _pan_start = _mouse;
            break;

        case evt_RIGHTBUTTON_RELEASED:
            PanMode( false );
            break;

        case evt_MIDBUTTON_PRESSED:
            ZoomMode( true );
            _zoom_start = _mouse;
            break;

        case evt_MIDBUTTON_RELEASED:
            ZoomMode( false );
            break;
    }
}

void Event::KeyEvent( SDL_KeyboardEvent& key )
{
    switch( key.keysym.sym )
    {
        case SDLK_w:
            PushCommand( cmd_TOGGLE_WIREFRAME );
            break;

        case SDLK_b:
            PushCommand( cmd_TOGGLE_BACKGROUND );
            break;

        case SDLK_s:
            PushCommand( cmd_TOGGLE_FOREGROUND );
            break;
            
        case SDLK_p:
            PushCommand( cmd_TOGGLE_PANEL );
            break;
            
        case SDLK_q:
        case SDLK_ESCAPE:
            _quit_condition = true;
            break;

        case SDLK_LSHIFT:
            _speed_factor = Config::Instance()->speed_factor_max;
            break;

        case SDLK_UP:
            PushCommand( cmd_UP );
            break;

        case SDLK_DOWN:
            PushCommand( cmd_DOWN );
            break;

        case SDLK_LEFT:
            PushCommand( cmd_LEFT );
            break;

        
        case SDLK_RIGHT:
            PushCommand( cmd_RIGHT );
            break;

        case SDLK_LCTRL:
            PushCommand( cmd_FIRE );
            break;
      
        default:
            break;
    }
}

void Event::PushEvent( EventType code )
{
    _event_queue.push( code );
}

Event::EventType Event::PopEvent()
{
    EventType code = evt_NONE;
    if( !_event_queue.empty() )
    {
        code = _event_queue.front();
        _event_queue.pop();
    }

    return code;
}

void Event::PushCommand( CommandType code ) 
{
    if( code != cmd_NONE )
    {
        _command_queue.push( code );
    }
}

void Event::MotionEvent( SDL_MouseMotionEvent& motion )
{
    _mouse.x = motion.x;
    _mouse.y = motion.y;

    PanUpdate();
    ZoomUpdate();
}

void Event::ButtonEvent( SDL_MouseButtonEvent& button )
{
    _mouse.x = button.x;
    _mouse.y = button.y;
    
    switch( button.button )
    {
        case SDL_BUTTON_LEFT:
            ProcessLeftButton(button);
            break;
            
        case SDL_BUTTON_RIGHT:
            ProcessRightButton(button);
            break;
            
        case SDL_BUTTON_MIDDLE:
            ProcessMiddleButton(button);
            break;

        case SDL_BUTTON_WHEELUP:
        case SDL_BUTTON_WHEELDOWN:
            WheelZoom( button );
            break;
            
        default:
            break;
    }
}

void Event::ProcessLeftButton( SDL_MouseButtonEvent& button )
{
    static int prevState = bs_UNDEFINED;
    int state = bs_UNDEFINED;
    
    switch( button.state ) {
        case SDL_PRESSED:
            state = bs_PRESSED;
            if( state != prevState ) {
                PushEvent( evt_LEFTBUTTON_PRESSED );
            }
            prevState = state;
            break;

        case SDL_RELEASED:
            state = bs_RELEASED;
            if( state != prevState ) {
                PushEvent( evt_LEFTBUTTON_RELEASED );
            }
            prevState = state;
            break;
    }
}

void Event::ProcessRightButton( SDL_MouseButtonEvent& button )
{
    static int prevState = bs_UNDEFINED;
    int state = bs_UNDEFINED;

    switch( button.state ) {
        case SDL_PRESSED:
            state = bs_PRESSED;
            if( state != prevState ) {
                PushEvent( evt_RIGHTBUTTON_PRESSED );
            }
            prevState = state;
            break;

        case SDL_RELEASED:
            state = bs_RELEASED;
            if( state != prevState ) {
                PushEvent( evt_RIGHTBUTTON_RELEASED );
            }
            prevState = state;
            break;
    }
}

void Event::ProcessMiddleButton( SDL_MouseButtonEvent& button )
{
    static int prevState = bs_UNDEFINED;
    int state = bs_UNDEFINED;

    switch( button.state ) {
        case SDL_PRESSED:
            state = bs_PRESSED;
            if( state != prevState ) {
                PushEvent( evt_MIDBUTTON_PRESSED );
            }
            prevState = state;
            break;

        case SDL_RELEASED:
            state = bs_RELEASED;
            if( state != prevState ) {
                PushEvent( evt_MIDBUTTON_RELEASED );
            }
            prevState = state;
            break;
    }
}

void Event::Poll()
{
    SDL_Event event;
    
    while( SDL_PollEvent(&event) )
    {
        switch( event.type )
        {
            case SDL_KEYDOWN:
                KeyEvent( event.key );
                break;

            case SDL_KEYUP:
                _speed_factor = Config::Instance()->speed_factor_min;
                break;

            case SDL_MOUSEMOTION:
                MotionEvent( event.motion );
                break;

            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                ButtonEvent( event.button );
                break;

            case SDL_QUIT:
                _quit_condition = true;
                break;
        }
    }
}

Event::CommandType Event::GetCommand()
{
    CommandType command_code = cmd_NONE;

    if( !_command_queue.empty() )
    {
        command_code = _command_queue.front();
        _command_queue.pop();
    }

    return command_code;
}

void Event::GetMousePosition( Vector2i& mouse )
{
    mouse = _mouse;
}
