#ifndef GAMETEXT_H
#define GAMETEXT_H

#include <font.h>
#include <layer.h>

class GameText : public Layer
{
    public:
        GameText();
        ~GameText();
        bool Init( Volume& viewport );
        void Render();
        void Resize(int width, int height);
        void ProcessCommand( Event::CommandType cmdCode );

    private:
        void Defaults();
        void RenderGameOver();
        void RenderScore();

    private:
        std::string _game_over_text;
        int _game_over_font_size;
        double _game_over_width;
        double _game_over_height;
        int _game_over_x;
        int _game_over_y;
        Font* _game_over_font;
        
};

#endif
