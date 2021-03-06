#include <GL/gl.h>
#include <version.h>
#include <config.h>
#include <panel.h>
#include <gamestate.h>

PanelLayer::PanelLayer()
{
    puts("PanelLayer::PanelLayer()");

    Defaults();
}

PanelLayer::~PanelLayer()
{
    puts("PanelLayer::~PanelLayer()");

    delete _writer;
}

void PanelLayer::Defaults()
{
    // These values will be calculated on resize.
    _frame.left = -1;
    _frame.right = -1;
    _frame.bottom = -1;
    _frame.top = -1;

    _margin = Config::Instance()->panel_margin;
    _panel_percent = Config::Instance()->panel_percent;

    _visible = true;

    _frame_width = Config::Instance()->frame_width;

    _frame_color[0] = Config::Instance()->frame_color_red;
    _frame_color[1] = Config::Instance()->frame_color_green;
    _frame_color[2] = Config::Instance()->frame_color_blue;
    _frame_color[3] = Config::Instance()->frame_color_alpha;
   
    _panel_color[0] = Config::Instance()->panel_color_red;
    _panel_color[1] = Config::Instance()->panel_color_green;
    _panel_color[2] = Config::Instance()->panel_color_blue;
    _panel_color[3] = Config::Instance()->panel_color_alpha;

    _font_color[0] = Config::Instance()->font_color_red;
    _font_color[1] = Config::Instance()->font_color_green;
    _font_color[2] = Config::Instance()->font_color_blue;
    _font_color[3] = Config::Instance()->font_color_alpha;
}

bool PanelLayer::Init( Volume& viewport )
{
    bool result = true;

    _use_screen_coords = true;
    Layer::Init( viewport );

// TODO : [REVISE] Do we still need to assign these? Check.
    _zoom_factor = 0.0;
    _pan_factor = 0.0;

    _writer = Writer::Instance();
    if( _writer->Init() == false ) {
        puts("Writer::Init() ERROR!");
    }

    _writer->SetColor( _font_color );

    // TODO : Find and alternate way and place to show version string.
    Writer::Instance()->Add( VERSION_STRING );

    return result;
}

void PanelLayer::Resize( int width, int height )
{
    Layer::Resize(width, height);

    _frame.left = _margin;
    _frame.right = width - _margin;
    _frame.bottom = height - _margin;
    _frame.top = height * ( 100 - _panel_percent ) / 100.0;

// TODO : [PROPOSAL] Also, an update for window limits would be suitable. Even if just for cropping.
    Vector2i origin(_frame.left, _frame.top);
    _writer->UpdateOrigin( origin );
}

void PanelLayer::Toggle() {

    _visible = not _visible;
}

void PanelLayer::Render()
{
    if( _visible ) {

        PreRender();
        RenderPanel();
        RenderContent();
        PostRender();
    }
}

void PanelLayer::RenderPanel()
{
    // Background
    glColor4dv( _panel_color );
    glBegin( GL_QUADS );
        glVertex2d( _frame.left, _frame.top );
        glVertex2d( _frame.right, _frame.top );
        glVertex2d( _frame.right, _frame.bottom );
        glVertex2d( _frame.left, _frame.bottom );
    glEnd();

    // Frame
    glLineWidth( _frame_width );
    glColor4dv( _frame_color );
    glBegin( GL_LINE_LOOP );
        glVertex2d( _frame.left, _frame.top );
        glVertex2d( _frame.right, _frame.top );
        glVertex2d( _frame.right, _frame.bottom );
        glVertex2d( _frame.left, _frame.bottom );
    glEnd();
}

void PanelLayer::RenderContent()
{
    _writer->Render();
}

void PanelLayer::ProcessCommand( Command* cmd )
{
    Command::CommandType code;

    if( cmd != 0 )
    {
        code = cmd->Code( (int) GameState::Instance()->State() );
        switch( code )
        {
            case Command::cmd_TOGGLE_PANEL:
                Toggle(); break;

            default:
                break;
        }
    }
}
