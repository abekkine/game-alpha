#ifndef MENU_H
#define MENU_H

#include <font.h>
#include <layer.h>

class Menu : public Layer
{
    public:
        Menu();
        ~Menu();
        bool Init( Volume& viewport );
        void Render();
        void Resize(int width, int height);
        void ProcessCommand( Event::CommandType cmdCode );

    private:
        void Defaults();
        void RenderOptions();


    private:
        int _font_height;
        int _line_step;
        Font* _font;
        Vector2i _cursor;
        Vector2i _origin;
        std::vector< std::string > _options;
};

#endif

