#ifndef FONT_H
#define FONT_H

#include <string>

#include <GL/gl.h>
#include <FTGL/ftgl.h>

class Font
{
    public:
        Font();
        ~Font();
        bool Init();
        void SetColor( double* color );
        void Box( std::string text );
        double Width();
        double Height();
        void Size( int size );
        void Face( std::string name );
        void Print( int x, int y, std::string text );

    private:
        // Members
        FTBBox _box;
        FTGLPixmapFont* _font;
        double _font_color[4];
        std::string _font_name;
        std::string _font_path;
        std::string _font_folder;
        int _font_size;
        double _width;
        double _height;
};

#endif

