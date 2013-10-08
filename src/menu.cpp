#include <GL/gl.h>

#include <string>

#include <gamestate.h>
#include <menu.h>

Menu::Menu()
{
    Defaults();
}

Menu::~Menu()
{
}

void Menu::Defaults()
{
    _font = 0;
    _font_height = 20;
    _line_step = 10;

    _origin.x = 10;
    _origin.y = 10+_font_height;

    _cursor = _origin;
}

bool Menu::Init(Volume& viewport)
{
    bool result = true;

    _use_screen_coords = true;
    Layer::Init( viewport );

    _zoom_factor = 0.0;
    _pan_factor = 0.0;

    _font = new Font();
    _font->Size(_font_height);

    result = _font->Init();

    _options.clear();
    _options.push_back("START");
    _options.push_back("EXIT");

    return result;
}

void Menu::Render()
{
    PreRender();
    RenderOptions();
    PostRender();
}

void Menu::Resize(int width, int height)
{
    Layer::Resize(width, height);
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

void Menu::RenderOptions()
{
    std::vector< std::string >::iterator iOption;

    _cursor = _origin;
    for(iOption=_options.begin(); iOption!=_options.end(); ++iOption)
    {
        _font->Print( _cursor.x, _cursor.y, *iOption );
        _cursor.y += _font_height+_line_step;
    }
}

