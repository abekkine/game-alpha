#ifndef PANEL_H
#define PANEL_H

#include <string>

#include <definitions.h>
#include <writer.h>
#include <layer.h>

class Menu : public Layer
{
    public:
        Menu();
        ~Menu();
        bool Init( Volume& viewport );
        void Resize( int width, int height );
        void Toggle();
        void Render();

    private:
        // Methods
        void Defaults();
        void RenderMenu();
        void RenderContent();

    private:
        // Members
        Writer* _writer;
        bool _visible;
        int _margin;
        int _menu_percent;
        Volume _frame;

        double _frame_width;
        double _font_color[4];
        double _menu_color[4];
        double _frame_color[4];
};

#endif

