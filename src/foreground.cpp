#include <stdio.h>

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
    _move_horizontal = move_NONE;
    _player_x = 0.0;
    _player_y = -0.36;
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
    RenderPlayer();
    RenderObstacles();
    RenderEnemy();
    RenderScore();
}

void Foreground::RenderGround()
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

void Foreground::RenderPlayer()
{
    static double w = 0.02;
    static double h = 0.06;
    glPushMatrix();
    glLoadIdentity();
    glTranslated( _player_x, _player_y, 0.0 );
    // Ship
    glColor3d( 1.0, 1.0, 1.0 );
    glBegin( GL_TRIANGLES );
    glVertex2d( 0.0, h );
    glVertex2d(  w, 0.0 );
    glVertex2d( -w, 0.0 );
    glEnd();
    // Shadow
    glColor3d( 0.3, 0.3, 0.3 );
    glBegin( GL_QUADS );
    glVertex2d( -w, -0.01 );
    glVertex2d( -w, -0.02 );
    glVertex2d(  w, -0.02 );
    glVertex2d(  w, -0.01 );
    glEnd();
    glPopMatrix();

    switch( _move_horizontal ) {
        case move_LEFT:
            _player_x -= 0.005; break;
        case move_RIGHT:
            _player_x += 0.005; break;
        default:
            break;
    }
}

void Foreground::RenderObstacles()
{
}

void Foreground::RenderEnemy()
{
}

void Foreground::RenderScore()
{
}

void Foreground::ProcessCommand( Event::CommandType cmdCode )
{
    if( cmdCode != Event::cmd_NONE )
    {
        switch( cmdCode )
        {
            case Event::cmd_TOGGLE_WIREFRAME:
                ToggleWireframe(); break;
            case Event::cmd_TOGGLE_FOREGROUND:
                Toggle(); break;
            case Event::cmd_LEFT_ENABLE:
                _move_horizontal = move_LEFT; break;
            case Event::cmd_LEFT_DISABLE:
                _move_horizontal = move_NONE; break;
            case Event::cmd_RIGHT_ENABLE:
                _move_horizontal = move_RIGHT; break;
            case Event::cmd_RIGHT_DISABLE:
                _move_horizontal = move_NONE; break;

            case Event::cmd_UP:
            case Event::cmd_DOWN:
            case Event::cmd_FIRE:
                puts("Player action!");
            default:
                break;
        }
    }
}

