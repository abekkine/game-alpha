#include <GL/gl.h>

#include <gamestate.h>
#include <menu.h>

Menu::Menu()
{
}

Menu::~Menu()
{
}

bool Menu::Init(Volume& viewport)
{
    bool result = true;

    Layer::Init( viewport );

    _zoom_factor = 1.0;
    _pan_factor = 1.0;

    return result;
}

void Menu::Render()
{
    PreRender();
    RenderOptions();
    PostRender();
}

void Menu::ProcessCommand(Event::CommandType cmdCode)
{
    if( cmdCode != Event::cmd_NONE )
    {
        switch( cmdCode )
        {
            case Event::cmd_UP:
                break;
            case Event::cmd_DOWN:
                break;
            case Event::cmd_SELECT:
                GameState::Instance()->State(GameState::gsPLAY);
                break;
            default:
                break;
        }
    }
}

void Menu::Defaults()
{
}

void Menu::RenderOptions()
{
    const double SIZE = 0.1;
    glPushMatrix();
    glLoadIdentity();
    glTranslated(0.0, 0.0, 0.0);
    glColor3d( 1.0, 1.0, 1.0 );
    glBegin( GL_QUADS );
    glVertex2d( -SIZE, -SIZE );
    glVertex2d( -SIZE,  SIZE );
    glVertex2d(  SIZE,  SIZE );
    glVertex2d(  SIZE, -SIZE );
    glEnd();
    glPopMatrix();
}

