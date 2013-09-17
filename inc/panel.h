#ifndef PANEL_H
#define PANEL_H

#include <string>

#include <definitions.h>
#include <writer.h>
#include <layer.h>

class Panel : public Layer
{
    public:
        Panel();
        ~Panel();
        bool Init( Volume& viewport );
        void Resize( int width, int height );
        void Toggle();
        void Render();

    private:
        // Methods
        void Defaults();
        void RenderPanel();
        void RenderContent();

    private:
        // Members
        Writer* _writer;
        bool _visible;
        int _margin;
        int _panel_percent;
        Volume _frame;

        double _frame_width;
        double _font_color[4];
        double _panel_color[4];
        double _frame_color[4];
};

#endif

