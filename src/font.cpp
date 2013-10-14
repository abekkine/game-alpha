#include <string.h>

#include <config.h>
#include <font.h>

Font::Font()
{
    puts("Font::Font()");

    _font_name = Config::Instance()->font_name;
    _font_folder = Config::Instance()->font_folder;
    _font_size = Config::Instance()->font_size;

    _width = -1.0;
    _height = -1.0;

    _font_color[0] = 1.0;
    _font_color[1] = 1.0;
    _font_color[2] = 1.0;
    _font_color[3] = 1.0;
}

Font::~Font()
{
    puts("Font::~Font()");

    delete _font;
}

bool Font::Init()
{
    bool result = false;

    _font_path = _font_folder + _font_name;
    
    _font = new FTGLPixmapFont( _font_path.c_str() );
    
    if( ! _font->Error() )
    {
        _font->FaceSize( _font_size );
        result = true;
    }

    return result;
}

void Font::SetColor( double* color ) {

    memcpy( _font_color, color, 4 * sizeof(double) );
}

void Font::Size( int size ) {

    _font_size = size;
}

void Font::Face( std::string name )
{
    _font_name = name;
}

void Font::Box( std::string text )
{
    _box = _font->BBox( text.c_str() );
    _width = _box.Upper().X() - _box.Lower().X();
    _height = _box.Upper().Y() - _box.Lower().Y();
}

double Font::Width()
{
    return _width;
}

double Font::Height()
{
    return _height;
}

void Font::Print( int x, int y, std::string text )
{
    glColor4dv( _font_color );

    glRasterPos2i( x, y );
    _font->Render( text.c_str() );
}

