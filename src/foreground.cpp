#include <stdio.h>
//#include <GL/gl.h>

#include <vector.h>
#include <config.h>
#include <writer.h>
#include <foreground.h>

Foreground::Foreground()
{
    puts("Foreground::Foreground()");

    Defaults();
}

Foreground::~Foreground()
{
    puts("Foreground::~Foreground()");
}

void Foreground::Defaults()
{
    _visible = true;
    _wireframe = false;

    _zoom_factor = 0.0;
    _pan_factor = 0.0;
}

bool Foreground::Init( Volume& viewport )
{
    bool result = true;

    Layer::Init( viewport );
   
    _zoom_factor = Config::Instance()->foreground_zoom_factor;
    _pan_factor = Config::Instance()->foreground_pan_factor;

    Writer::Instance()->Add("X( %f )", &_viewport.left );
    Writer::Instance()->Add("Y( %f )", &_viewport.bottom );

    return result;
}

void Foreground::Toggle() {

    _visible = not _visible;
}

void Foreground::ToggleWireframe() {

    _wireframe = not _wireframe;
}

void Foreground::Render()
{

    if( _visible ) {

        PreRender();
        RenderForegroundLayer();
        PostRender();
    }
}

void Foreground::RenderForegroundLayer()
{
    // TODO : Game foreground objects (enemies, player, obstacles, etc.) will be rendered here.
    static double alpha = 0.0;
    alpha += 2.5;
    glPushMatrix();
    glLoadIdentity();
    glTranslated( 0.0, 0.0, 0.0 );
    glRotated( alpha, 0.0, 0.0, 1.0 );
    glColor3d( 1.0, 1.0, 1.0 );
    glBegin( GL_LINE_LOOP );
    glVertex2d( -0.1, -0.1 );
    glVertex2d( -0.1,  0.1 );
    glVertex2d(  0.1,  0.1 );
    glVertex2d(  0.1, -0.1 );
    glEnd();
    glPopMatrix();
    // END
}

