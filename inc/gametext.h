#ifndef GAMETEXT_H
#define GAMETEXT_H

#include <font.h>
#include <layer.h>

class GameTextLayer : public Layer
{
    public:
        GameTextLayer();
        ~GameTextLayer();
        bool Init( Volume& viewport );
        void Render();
        void Resize(int width, int height);
        void ProcessCommand( Command* cmd );
        void ShowHealth( double health );
        void ShowScore( int score );

    private:
        void Defaults();
        void RenderPlayerHealth();
        void RenderGameOver();
        void RenderScore();
        void UpdateCoordinates();
        void ScoreToString();

    private:
        // Game Over stuff.
        std::string _game_over_text;
        int _game_over_font_size;
        double _game_over_width;
        double _game_over_height;
        int _game_over_x;
        int _game_over_y;
        Font* _game_over_font;

        // Score stuff.
        std::string _score_text;
        int _score_font_size;
        double _score_width;
        double _score_height;
        int _score_x;
        int _score_y;
        Font* _score_font;

        // Other members.
        double _player_health;
        int _score;
};

#endif
