#include <GL/gl.h>
#include <sstream>

#include <config.h>
#include <gamestate.h>
#include <gametext.h>

GameTextLayer::GameTextLayer()
{
    Defaults();
}

GameTextLayer::~GameTextLayer()
{
}

void GameTextLayer::Defaults()
{
    // Game over stuff.
    _game_over_font_size = 40;
    _game_over_font = 0;
    _game_over_width = 0.0;
    _game_over_height = 0.0;
    _game_over_x = 0;
    _game_over_y = 0;

    // Score stuff.
    _score_text = "";
    _score_font_size = 40;
    _score_width = 0.0;
    _score_height = 0.0;
    _score_x = 0;
    _score_y = 0;
    _score_font = 0;

    // Other stuff.
    _player_health = 0.0;
    _score = 0;
}

bool GameTextLayer::Init(Volume& viewport)
{
    bool result = true;

    _use_screen_coords = true;
    Layer::Init( viewport );

    _zoom_factor = 0.0;
    _pan_factor = 0.0;

    // Game over stuff.
    _game_over_font = new Font();
    _game_over_font->Size(_game_over_font_size);
    _game_over_font->Init();

    _game_over_text = "GAME OVER";
    _game_over_font->Box( _game_over_text );
    _game_over_width = _game_over_font->Width();
    _game_over_height = _game_over_font->Height();
    _game_over_x = 0.5 * (Config::Instance()->screen_width - _game_over_width);
    _game_over_y = 0.5 * (Config::Instance()->screen_height - _game_over_height);

    // Score stuff.
    _score_font = new Font();
    _score_font->Size(_score_font_size);
    _score_font->Init();

    _score = 0;
    ScoreToString();
    UpdateCoordinates();

    return result;
}

void GameTextLayer::UpdateCoordinates()
{
    _score_font->Box( _score_text );
    _score_width = _score_font->Width();
    _score_height = _score_font->Height();
    _score_x = Config::Instance()->screen_width - (_score_width + 10.0);
    _score_y = 10.0+_score_height;
}

void GameTextLayer::ScoreToString()
{
    std::ostringstream s;
    s << _score;
    _score_text = std::string( s.str() );
}

void GameTextLayer::Render()
{
    PreRender();

    RenderPlayerHealth();
    // TODO : It would be nice to call State's Render() method, instead of checking what state is.
    if( GameState::Instance()->State() == GameState::gsGAMEOVER )
    {
        RenderGameOver();
    }

    RenderScore();
    PostRender();
}

void GameTextLayer::Resize(int width, int height)
{
    Layer::Resize(width, height);
}

void GameTextLayer::ProcessCommand(Command* cmd)
{
    cmd = cmd;
}

void GameTextLayer::RenderPlayerHealth()
{
    const double fWIDTH = 80.0;
    const double fHEIGHT = 20.0;
    double bar_width = 0.0;

    _player_health = GameState::Instance()->Health();

    glPushMatrix();
    glLoadIdentity();
    glTranslated(20.5, 20.5, 0.0);
    // Health Filler
    bar_width = fWIDTH * _player_health;
    glColor3d( 1.0, 0.0, 0.0 );
    glBegin(GL_QUADS);
        glVertex2d(0.0, 0.0);
        glVertex2d(bar_width, 0.0);
        glVertex2d(bar_width, fHEIGHT);
        glVertex2d(0.0, fHEIGHT);
    glEnd();
    // Health Frame
    glLineWidth(1.2);
    glColor3d( 1.0, 1.0, 1.0 );
    glBegin(GL_LINE_LOOP);
        glVertex2d( 0.0, 0.0 );
        glVertex2d( fWIDTH, 0 );
        glVertex2d( fWIDTH, fHEIGHT );
        glVertex2d( 0, fHEIGHT );
    glEnd();
    glPopMatrix();
}

void GameTextLayer::RenderGameOver()
{
    double gameOverColor[] = { 0.75, 0.0, 0.0, 1.0 };

    _game_over_font->SetColor( gameOverColor );
    _game_over_font->Print( _game_over_x, _game_over_y, _game_over_text );
}

void GameTextLayer::RenderScore()
{
    // TODO : for rendering score.
    double scoreColor[] = { 1.0, 1.0, 0.0, 1.0 };

    _score = GameState::Instance()->Score();

    ScoreToString();
    UpdateCoordinates();
    _score_font->SetColor( scoreColor );
    _score_font->Print( _score_x, _score_y, _score_text );
}

