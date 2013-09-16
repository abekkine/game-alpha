#include <GL/gl.h>
#include <version.h>
#include <config.h>
#include <menu.h>

Menu::Menu()
{
    puts("Menu::Menu()");

    Defaults();
}

Menu::~Menu()
{
    puts("Menu::~Menu()");

    delete _writer;
}

void Menu::Defaults()
{
    // These values will be calculated on resize.
    _frame.left = -1;
    _frame.right = -1;
    _frame.bottom = -1;
    _frame.top = -1;

    _margin = Config::Instance()->menu_margin;
    _menu_percent = Config::Instance()->menu_percent;

    _visible = true;

    _frame_width = Config::Instance()->frame_width;

    _frame_color[0] = Config::Instance()->frame_color_red;
    _frame_color[1] = Config::Instance()->frame_color_green;
    _frame_color[2] = Config::Instance()->frame_color_blue;
    _frame_color[3] = Config::Instance()->frame_color_alpha;
   
    _menu_color[0] = Config::Instance()->menu_color_red;
    _menu_color[1] = Config::Instance()->menu_color_green;
    _menu_color[2] = Config::Instance()->menu_color_blue;
    _menu_color[3] = Config::Instance()->menu_color_alpha;

    _font_color[0] = Config::Instance()->font_color_red;
//DEBUG
    printf("font_color_red(%f)\n", _font_color[0] );
//END
    _font_color[1] = Config::Instance()->font_color_green;
    _font_color[2] = Config::Instance()->font_color_blue;
    _font_color[3] = Config::Instance()->font_color_alpha;
}

bool Menu::Init( Volume& viewport )
{
    bool result = true;

    Layer::Init( viewport );

    _use_screen_coords = true;
// TODO : [REVISE] Do we still need to assign these? Check.
    _zoom_factor = 0.0;
    _pan_factor = 0.0;

    _writer = Writer::Instance();
    if( _writer->Init() == false ) {
        puts("Writer::Init() ERROR!");
    }

    //DEBUG
    printf("_font_color(%f, %f, %f, %f)\n", _font_color[0], _font_color[1], _font_color[2], _font_color[3]);
    //END
    _writer->SetColor( _font_color );

    // TODO : Find and alternate way and place to show version string.
    Writer::Instance()->Add( VERSION_STRING );

    return result;
}

void Menu::Resize( int width, int height )
{
    Layer::Resize(width, height);

    _frame.left = _margin;
    _frame.right = width - _margin;
    _frame.bottom = height - _margin;
    _frame.top = height * ( 100 - _menu_percent ) / 100.0;

// TODO : [PROPOSAL] Also, an update for window limits would be suitable. Even if just for cropping.
    Vector2i origin(_frame.left, _frame.top);
    _writer->UpdateOrigin( origin );
}

void Menu::Toggle() {

    _visible = not _visible;
}

void Menu::Render()
{
    if( _visible ) {

        PreRender();
        RenderMenu();
        RenderContent();
        PostRender();
    }
}

void Menu::RenderMenu()
{
    // Background
    glColor4dv( _menu_color );
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

void Menu::RenderContent()
{
    _writer->Render();
}

