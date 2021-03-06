#include <stdio.h>

#include <vector.h>
#include <config.h>
#include <writer.h>
#include <foreground.h>
#include <objectmanager.h>
#include <effectmanager.h>
#include <gamestate.h>

ForegroundLayer::ForegroundLayer()
{
    puts("ForegroundLayer::ForegroundLayer()");

    Defaults();
}

ForegroundLayer::~ForegroundLayer()
{
    puts("ForegroundLayer::~ForegroundLayer()");
}

void ForegroundLayer::Defaults()
{
    _visible = true;
    _wireframe = false;

    _zoom_factor = 0.0;
    _pan_factor = 0.0;
}

bool ForegroundLayer::Init( Volume& viewport )
{
    bool result = true;

    Layer::Init( viewport );
   
    _zoom_factor = Config::Instance()->foreground_zoom_factor;
    _pan_factor = Config::Instance()->foreground_pan_factor;

    Writer::Instance()->Add("X( %f )", &_viewport.left );
    Writer::Instance()->Add("Y( %f )", &_viewport.bottom );

    return result;
}

void ForegroundLayer::Toggle() {

    _visible = not _visible;
}

void ForegroundLayer::ToggleWireframe() {

    _wireframe = not _wireframe;
}

void ForegroundLayer::Render()
{
    if( _visible ) {

        PreRender();
        RenderForegroundLayer();
        PostRender();
    }
}

void ForegroundLayer::RenderForegroundLayer()
{
    // TODO : Game foreground objects (enemies, player, obstacles, etc.) will be rendered here.
    if( Config::Instance()->debug ) {
        static double alpha = 0.0;
        const double SIZE = 0.1;
        alpha += 0.05;
        glPushMatrix();
        glLoadIdentity();
        glTranslated( 0.0, 0.0, 0.0 );
        glRotated( alpha, 0.0, 0.0, 1.0 );
        glColor3d( 0.6, 0.6, 0.6 );
        glBegin( GL_LINE_LOOP );
        glVertex2d( -SIZE, -SIZE );
        glVertex2d( -SIZE,  SIZE );
        glVertex2d(  SIZE,  SIZE );
        glVertex2d(  SIZE, -SIZE );
        glEnd();
        glPopMatrix();
    }

    RenderGround();

    ObjectManager::Instance()->Render();
    EffectManager::Instance()->Render();
}

void ForegroundLayer::RenderGround()
{

    static double w = 1.0;
    static double h = 0.1;
    glPushMatrix();
    glLoadIdentity();
    glTranslated( 0.0, -0.45, 0.0 );
    glColor3d( 0.4, 0.4, 0.4 );
    glBegin( GL_QUADS );
    glVertex2d( -w, -h );
    glVertex2d( -w,  h );
    glVertex2d(  w,  h );
    glVertex2d(  w, -h );
    glEnd();
    glPopMatrix();
}

void ForegroundLayer::ProcessCommand( Command* cmd )
{
    Command::CommandType code;

    if( cmd != 0 )
    {
        code = cmd->Code((int) GameState::Instance()->State());
        switch( code )
        {
            case Command::cmd_TOGGLE_WIREFRAME:
                ToggleWireframe(); break;
            case Command::cmd_TOGGLE_FOREGROUND:
                Toggle(); break;
            case Command::cmd_UP:
            case Command::cmd_DOWN:
                break;

            default:
                break;
        }
    }
}
