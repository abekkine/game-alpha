#include <GL/gl.h>

#include <string>

#include <gamestate.h>
#include <menu.h>

MenuLayer::MenuLayer()
{
    Defaults();
}

MenuLayer::~MenuLayer()
{
}

void MenuLayer::Defaults()
{
    _font = 0;
    _font_height = 20;
    _line_step = 10;

    _origin.x = 10;
    _origin.y = 10+_font_height;

    _cursor = _origin;
    _selected_id = 0;
}

bool MenuLayer::Init(Volume& viewport)
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
    _options[ 0 ] = "START";
    _options[ 1 ] = "EXIT";

    return result;
}

void MenuLayer::Render()
{
    PreRender();
    RenderOptions();
    PostRender();
}

void MenuLayer::Resize(int width, int height)
{
    Layer::Resize(width, height);
}

// TODO : ProcessCommand is Update code for menu.
void MenuLayer::ProcessCommand(Command* cmd)
{
    Command::CommandType code;

    if( cmd != 0 )
    {
        code = cmd->Code((int) GameState::Instance()->State());
        switch( code )
        {
            case Command::cmd_UP:
                if( _selected_id != 0 ) {
                    _selected_id = 0;
                }
                break;

            case Command::cmd_DOWN:
                if( _selected_id != 1 ) {
                    _selected_id = 1;
                }
                break;

            case Command::cmd_SELECT:
                if( _selected_id == 0 ) {
// TODO : game initialization before play (See #24).
//      : after initialization complete, set game state to gsPLAY.
//                    GameState::Instance()->State(GameState::gsINIT);
                    GameState::Instance()->State(GameState::gsPLAY);
                }
                else {
                    GameState::Instance()->State(GameState::gsQUIT);
                }
                break;

            default:
                break;
        }
    }
}

void MenuLayer::RenderOptions()
{
    // TODO : Optimize
    double selectionColor[] = { 1.0, 1.0, 0.0, 1.0 };
    double textColor[] = { 1.0, 1.0, 1.0, 1.0 };

    std::map< int, std::string >::iterator iOption;

    _cursor = _origin;
    for(iOption=_options.begin(); iOption!=_options.end(); ++iOption)
    {
        if( iOption->first == _selected_id )
        {
            _font->SetColor( selectionColor );
            _font->Print( _cursor.x, _cursor.y, ">" );
        }
        _font->SetColor( textColor );
        _font->Print( _cursor.x+10, _cursor.y, iOption->second );
        _cursor.y += _font_height+_line_step;
    }
}

