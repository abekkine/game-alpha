#include <stdio.h>
#include <math.h>
#include <GL/gl.h>

#include <config.h>
#include <writer.h>
#include <background.h>
#include <gamestate.h>

BackgroundLayer::BackgroundLayer()
{
    puts("BackgroundLayer::BackgroundLayer()");

    Defaults();
}

BackgroundLayer::~BackgroundLayer()
{
    puts("BackgroundLayer::~BackgroundLayer()");
}

void BackgroundLayer::Defaults()
{
    _visible = true;
    _wireframe = false;
}

bool BackgroundLayer::Init( Volume& viewport )
{
    bool result = true;

    Layer::Init( viewport );

    _zoom_factor = Config::Instance()->bg_zoom_factor;
    _pan_factor = Config::Instance()->bg_pan_factor;
    
    return result;
}

void BackgroundLayer::ToggleWireframe()
{
    _wireframe = not _wireframe;
}

void BackgroundLayer::Toggle() {
    
    _visible = not _visible;
}

void BackgroundLayer::Render()
{
    if( _visible ) {

        PreRender();
        RenderBackground();
        PostRender();
    }
}

void BackgroundLayer::RenderBackground()
{
    // TODO : Render game background.
    if( Config::Instance()->debug ) {
        static double alpha = 0.0;
        const double SIZE = 0.05;
        // TODO : This calculations also should be in an Update() method.
        alpha += 0.3;
        glPushMatrix();
        glLoadIdentity();
        glTranslated( 0.0, 0.0, 0.0 );
        glRotated( alpha, 0.0, 0.0, -1.0 );
        glColor3d( 0.2, 0.2, 0.2 );
        glBegin( GL_LINE_LOOP );
        glVertex2d( -SIZE, -SIZE );
        glVertex2d( -SIZE,  SIZE );
        glVertex2d(  SIZE,  SIZE );
        glVertex2d(  SIZE, -SIZE );
        glEnd();
        glPopMatrix();
    }
}

void BackgroundLayer::ProcessCommand( Command* cmd )
{
    Command::CommandType code;

    if( cmd != 0 )
    {
        code = cmd->Code((int) GameState::Instance()->State());
        switch( code )
        {
            case Command::cmd_TOGGLE_WIREFRAME:
                ToggleWireframe(); break;
            case Command::cmd_TOGGLE_BACKGROUND:
                Toggle(); break;
            default:
                break;
        }
    }
}

