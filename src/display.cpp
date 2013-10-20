#include <version.h>
#include <config.h>
#include <writer.h>
#include <gamestate.h>
#include <display.h>
#include <objectmanager.h>

Display::Display()
{
    puts("Display::Display()");

    Defaults();
}

Display::~Display()
{
    puts("Display::~Display()");

    delete _fps_timer;
    delete _panel;
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
    _panel = 0;
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

    _menu = new MenuLayer();
    if( not _menu->Init( _viewport ) ) {
        fprintf( stderr, "Unable to initialize MenuLayer instance!\n" );
        result = false;
    } 
    _components.push_back( _menu );

    _gametext = new GameTextLayer();
    if( not _gametext->Init( _viewport ) ) {
        fprintf( stderr, "Unable to initialize GameTextLayer instance!\n" );
        result = false;
    }
    _components.push_back( _gametext );

    _panel = new PanelLayer();
    if( not _panel->Init( _viewport ) ) {
        fprintf( stderr, "Unable to initialize PanelLayer instance!\n" );
        result = false;
    }
    _components.push_back( _panel );

    _background = new BackgroundLayer();
    if( not _background->Init( _viewport ) ) {
        fprintf( stderr, "Unable to initialize BackgroundLayer instance!\n" );
        result = false;
    }
    _components.push_back( _background );

    _foreground = new ForegroundLayer();
    if( not _foreground->Init( _viewport ) ) {
        fprintf( stderr, "Unable to initialize ForegroundLayer instance!\n" );
        result = false;
    }
    _components.push_back( _foreground );

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
    _panel->Resize( width, height );
    _menu->Resize( width, height );
}

void Display::RenderScene()
{
    _fps = _fps_timer->GetFPS();

    switch( GameState::Instance()->State() )
    {

        case GameState::gsPLAY:
        case GameState::gsGAMEOVER:
            _background->Render();
            _foreground->Render();
            _gametext->Render();
            break;

        case GameState::gsMENU:
            _menu->Render();
            break;

        default:
            break;
    }
    
    _panel->Render();
}

void Display::Render()
{
    // Clear screen.
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    RenderScene();

    // Swap buffers.
    SDL_GL_SwapBuffers();

    Event::Instance()->Update();
        
    ProcessCommands();
}

void Display::ProcessCommands()
{
    std::vector< Layer * >::iterator iter;
    Layer* l;
    Command* cmd; 

    do {
        cmd = CommandManager::Instance()->Get();
        if( cmd != 0 )
        {
            for( iter = _components.begin(); iter != _components.end(); ++iter )
            {
                l = *iter;
                l->ProcessCommand( cmd );
            }

            if( (cmd->Code() == Command::cmd_ZOOM) || (cmd->Code() == Command::cmd_PAN) )
            {
                Reshape();
            }
        }

    } while( cmd != 0 );
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

