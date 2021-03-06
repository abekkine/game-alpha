#include <vector.h>
#include <config.h>
#include <event.h>
#include <panel.h>
#include <writer.h>
#include <gamestate.h>
#include <command.h>

Event* Event::_instance = 0;

int Event::_zoom_delta = 0;
Vector2i Event::_pan_delta(0, 0);

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

    Process();

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

        // -1 is for all layers.
        CommandManager::Instance()->Push(new Command(Command::cmd_PAN, -1) );

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

        CommandManager::Instance()->Push(new Command(Command::cmd_ZOOM, -1));

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
    CommandManager::Instance()->Push(new Command(Command::cmd_ZOOM, -1));
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

void Event::Process()
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

void Event::KeyEvent( SDL_KeyboardEvent& key, int state )
{
    int gState = (int) GameState::Instance()->State();

    switch( key.keysym.sym )
    {
        case SDLK_w:
            if( state == SDL_KEYDOWN ) {
                CommandManager::Instance()->Push( new Command(Command::cmd_TOGGLE_WIREFRAME, gState) );
            }
            break;

        case SDLK_b:
            if( state == SDL_KEYDOWN ) {
                CommandManager::Instance()->Push( new Command(Command::cmd_TOGGLE_BACKGROUND, gState) );
            }
            break;

        case SDLK_s:
            if( state == SDL_KEYDOWN ) {
                CommandManager::Instance()->Push( new Command(Command::cmd_TOGGLE_FOREGROUND, gState) );
            }
            break;
            
        case SDLK_p:
            if( state == SDL_KEYDOWN ) {
                CommandManager::Instance()->Push( new Command(Command::cmd_TOGGLE_PANEL, gState) );
            }
            break;
            
        case SDLK_q:
        case SDLK_ESCAPE:
            CommandManager::Instance()->Push( new Command(Command::cmd_QUIT, gState) );
            break;

        case SDLK_LSHIFT:
            if( state == SDL_KEYDOWN ) {
                _speed_factor = Config::Instance()->speed_factor_max;
            } else {
                _speed_factor = Config::Instance()->speed_factor_min;
            }
            break;

        case SDLK_RETURN:
            CommandManager::Instance()->Push( new Command(Command::cmd_SELECT, gState) );
            break;

        case SDLK_UP:
            CommandManager::Instance()->Push( new Command(Command::cmd_UP, gState) );
            break;

        case SDLK_DOWN:
            CommandManager::Instance()->Push( new Command(Command::cmd_DOWN, gState) );
            break;

        case SDLK_LEFT:
            if( state == SDL_KEYDOWN ) {
                CommandManager::Instance()->Push( new Command(Command::cmd_LEFT_ENABLE, gState) );
            } else {
                CommandManager::Instance()->Push( new Command(Command::cmd_LEFT_DISABLE, gState) );
            }
            break;
        
        case SDLK_RIGHT:
            if( state == SDL_KEYDOWN ) {
                CommandManager::Instance()->Push( new Command(Command::cmd_RIGHT_ENABLE, gState) );
            } else {
                CommandManager::Instance()->Push( new Command(Command::cmd_RIGHT_DISABLE, gState) );
            }
            break;

        case SDLK_LCTRL:
            if( state == SDL_KEYDOWN ) {
                CommandManager::Instance()->Push( new Command(Command::cmd_FIRE, gState) );
            }
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
                KeyEvent( event.key, event.type );
                break;

            case SDL_KEYUP:
                KeyEvent( event.key, event.type );
                break;

            case SDL_MOUSEMOTION:
                MotionEvent( event.motion );
                break;

            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                ButtonEvent( event.button );
                break;

            case SDL_QUIT:
                CommandManager::Instance()->Push( new Command(Command::cmd_QUIT, (int) GameState::Instance()->State()) );
                break;
        }
    }
}

void Event::GetMousePosition( Vector2i& mouse )
{
    mouse = _mouse;
}
