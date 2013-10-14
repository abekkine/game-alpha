#ifndef MENU_H
#define MENU_H

#include <map>

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
        void ProcessCommand( Command* cmd );

    private:
        void Defaults();
        void RenderOptions();


    private:
        int _font_height;
        int _line_step;
        Font* _font;
        Vector2i _cursor;
        Vector2i _origin;
        int _selected_id;
        std::map< int, std::string > _options;
};

#endif

