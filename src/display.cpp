#include <version.h>
#include <config.h>
#include <writer.h>
#include <display.h>

Display::Display()
{
    puts("Display::Display()");

    Defaults();
}

Display::~Display()
{
    puts("Display::~Display()");

    delete _fps_timer;
    delete _menu;
    delete _event;
    delete _background;
    delete _foreground;
}

void Display::Defaults()
{
    // Frames per second.
    _fps = 0;
    Writer::Instance()->Add( "fps(%.1f)", &_fps );
    _fps_timer = 0;

    // Screen defaults.
    _screen = 0;
    _screen_width = Config::Instance()->screen_width;
    _screen_height = Config::Instance()->screen_height;

    // Background color from config.
    _clear_red = Config::Instance()->clear_color_red;
    _clear_green = Config::Instance()->clear_color_green;
    _clear_blue = Config::Instance()->clear_color_blue;
    _clear_alpha = 1.0;

    // Component defaults.
    _menu = 0;
    _event = 0;
    _background = 0;
    _foreground = 0;

    // Layer viewport
    _viewport.left = -0.5 * Config::Instance()->world_width;
    _viewport.right = 0.5 * Config::Instance()->world_width;
    _viewport.bottom = -0.5 * Config::Instance()->world_height;
    _viewport.top = 0.5 * Config::Instance()->world_height;
    _viewport.near = -1.0;
    _viewport.far = 1.0;
}

bool Display::Init()
{
    bool result = false;
    bool success;
    int rc;

    success = InitComponents();
    if( success )
    {

// TODO : [PROPOSAL] GLEW may be used instead of SDL library.
        rc = SDL_Init( SDL_INIT_VIDEO );
        if( rc < 0 )
        {
            fprintf( stderr, "Unable to init SDL : %s\n", SDL_GetError() );
        }
        else
        {
            atexit( SDL_Quit );

            _screen = SDL_SetVideoMode( _screen_width, _screen_height, 32, SDL_OPENGL );
            if( _screen == 0 )
            {
                fprintf( stderr, "Unable to set video mode %dx%d : %s\n", _screen_width, _screen_height, SDL_GetError() );
            }
            else
            {
                success = InitGL();
                if( success )
                {
                    Reshape( _screen->w, _screen->h );

                    result = true;
                }
            }
        }

    }

    return result;
}

bool Display::InitComponents()
{
    bool result = true;

    _fps_timer = new Timer();
    _fps_timer->Reset();

    _event = new Event();
    if( not _event->Init() ) {
        fprintf( stderr, "Unable to initialize Event instance!\n" );
        result = false;
    }

    _menu = new Menu();
    if( not _menu->Init( _viewport ) ) {
        fprintf( stderr, "Unable to initialize Menu instance!\n" );
        result = false;
    }

    _background = new Background();
    if( not _background->Init( _viewport ) ) {
        fprintf( stderr, "Unable to initialize Background instance!\n" );
        result = false;
    }

    _foreground = new Foreground();
    if( not _foreground->Init( _viewport ) ) {
        fprintf( stderr, "Unable to initialize Foreground instance!\n" );
        result = false;
    }

    return result;
}

bool Display::InitGL()
{
    bool result = true;

    glShadeModel( GL_SMOOTH );
    if( not CheckError() ) {
        result = false;
    }
    
    glClearColor( _clear_red, _clear_green, _clear_blue, _clear_alpha );
    if( not CheckError() ) {
        result = false;
    }
    
    glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
    if( not CheckError() ) {
        result = false;
    }

    // Enable blending and alpha channel.
    glEnable( GL_BLEND );
    if( not CheckError() ) {
        result = false;
    }
    
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    if( not CheckError() ) {
        result = false;
    }

    return result;    
}

void Display::Reshape()
{
    Reshape( _screen_width, _screen_height );
}

void Display::Reshape( int width, int height )
{
    if( height == 0 )
    {
        height = 1;
    }

    glViewport( 0, 0, width, height );

// TODO : [PROPOSAL] Following ones would be executed through a list.
    _background->Resize( width, height );
    _foreground->Resize( width, height );
    _menu->Resize( width, height );
}

void Display::Render()
{
    _fps = _fps_timer->GetFPS();

    _background->Render();
    _foreground->Render();
    _menu->Render();
}

void Display::Update()
{
    // Clear screen.
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    Render();

    // Swap buffers.
    SDL_GL_SwapBuffers();

    _event->Update();
        
    ProcessCommands();
}

void Display::ProcessCommands()
{
    Event::CommandType commandCode; 

    do {
        commandCode = _event->GetCommandCode();
        switch( commandCode ) {

            case Event::cmd_TOGGLE_WIREFRAME:
                ToggleWireframe();
                break;

            case Event::cmd_TOGGLE_BACKGROUND:
                _background->Toggle();
                break;

            case Event::cmd_TOGGLE_STAR:
                _foreground->Toggle();
                break;

            case Event::cmd_TOGGLE_PANEL:
                _menu->Toggle();
                break;

            case Event::cmd_ZOOM:
            case Event::cmd_PAN:
                Reshape();
                break;

            case Event::cmd_NONE:
                break;
        }
    } while( commandCode != Event::cmd_NONE );
}

// Following method will be used to trace and debug potential OpenGL errors.
bool Display::CheckError()
{
    bool result = false;
    GLenum errorCode = glGetError();

    switch( errorCode )
    {
        case GL_NO_ERROR:
            result = true;
            break;

        case GL_INVALID_ENUM:
            puts( "GL Invalid Enum" );
            break;

        case GL_INVALID_VALUE:
            puts( "GL Invalid Value" );
            break;

        case GL_INVALID_OPERATION:
            puts( "GL Invalid Operation" );
            break;

        case GL_STACK_OVERFLOW:
            puts( "GL Stack Overflow" );
            break;

        case GL_STACK_UNDERFLOW:
            puts( "GL Stack Underflow" );
            break;

        case GL_OUT_OF_MEMORY:
            puts( "GL Out of memory" );
            break;

        case GL_TABLE_TOO_LARGE:
            puts( "GL Table too large" );
            break;

        default:
            puts( "Unknown error" );
            break;
    }

    return result;
}

void Display::ToggleWireframe()
{
    _background->ToggleWireframe();
    _foreground->ToggleWireframe();
}

