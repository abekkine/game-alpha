#include <GL/gl.h>

#include <config.h>
#include <gamestate.h>
#include <gametext.h>

GameText::GameText()
{
    Defaults();
}

GameText::~GameText()
{
}

void GameText::Defaults()
{
    _game_over_font_size = 40;
    _game_over_font = 0;
    _game_over_width = 0.0;
    _game_over_height = 0.0;
    _game_over_x = 0;
    _game_over_y = 0;
}

bool GameText::Init(Volume& viewport)
{
    bool result = true;

    _use_screen_coords = true;
    Layer::Init( viewport );

    _zoom_factor = 0.0;
    _pan_factor = 0.0;

    _game_over_font = new Font();
    _game_over_font->Size(_game_over_font_size);
    _game_over_text = "GAME OVER";
    result = _game_over_font->Init();
    _game_over_font->Box( _game_over_text );
    _game_over_width = _game_over_font->Width();
    _game_over_height = _game_over_font->Height();
    _game_over_x = 0.5 * (Config::Instance()->screen_width - _game_over_width);
    _game_over_y = 0.5 * (Config::Instance()->screen_height - _game_over_height);

    return result;
}

void GameText::Render()
{
    PreRender();
    if( GameState::Instance()->State() == GameState::gsGAMEOVER )
    {
        RenderGameOver();
    }
    RenderScore();
    PostRender();
}

void GameText::Resize(int width, int height)
{
    Layer::Resize(width, height);
}

void GameText::ProcessCommand(Event::CommandType cmdCode)
{
    cmdCode = cmdCode;
}

void GameText::RenderGameOver()
{
    double gameOverColor[] = { 0.75, 0.0, 0.0, 1.0 };

    _game_over_font->SetColor( gameOverColor );
    _game_over_font->Print( _game_over_x, _game_over_y, _game_over_text );
}

void GameText::RenderScore()
{
    // TODO : for rendering score.
}
