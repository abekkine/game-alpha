#include <stdio.h>
#include <math.h>
#include <GL/gl.h>

#include <config.h>
#include <writer.h>
#include <background.h>

Background::Background()
:INTERIOR_ANGLE(M_PI/3.0),
WIRE_COLOR(0.15)
{
    puts("Background::Background()");

    Defaults();
}

Background::~Background()
{
    puts("Background::~Background()");

    delete _generator;
}

void Background::Defaults()
{
    _visible = true;
    _wireframe = false;

    _size_initial = 0.0;
    _size = 0.0;
    _height = 0.0;
    _halfSide = 0.0;
    _brightness = 0.2;

    _generator = 0;
}

bool Background::Init( Volume& viewport )
{
    bool result = true;

    Layer::Init( viewport );

    _zoom_factor = Config::Instance()->bg_zoom_factor;
    _pan_factor = Config::Instance()->bg_pan_factor;

    _size_initial = Config::Instance()->background_tile_size;
    _size = _size_initial;

    // Height and half of a side for equilateral triangle.
    _height = sin( INTERIOR_ANGLE ) * _size;
    _halfSide = cos( INTERIOR_ANGLE ) * _size;
    
    _red_offset = Config::Instance()->background_red_offset;
    _green_offset = Config::Instance()->background_green_offset;
    _blue_offset = Config::Instance()->background_blue_offset;

    _generator = new Generator();
// TODO : [IMPLEMENT] Background octave count should be changeable in runtime.
    _generator->SetOctaves( Config::Instance()->bg_octaves );

    return result;
}

void Background::ToggleWireframe()
{
    _wireframe = not _wireframe;
}

void Background::Toggle() {
    
    _visible = not _visible;
}

void Background::Render()
{
    if( _visible ) {

        PreRender();
        RenderBackground();
        PostRender();
    }
}

void Background::RenderBackground()
{
    Vector2d begin;
    Vector2d end;
    Vector2d begin_validated;
    Vector2d step;

    begin.x = _viewport.left;
    end.x = _viewport.right;
    end.y = _viewport.top;
    begin.y = _viewport.bottom;

    begin_validated.x = floor( begin.x );
    begin_validated.y = 2.0 * floor( 0.5 * begin.y / _height ) * _height; 

    for( step.x = begin_validated.x; step.x < end.x; step.x += _size )
    {
        for( step.y = begin_validated.y; step.y < end.y; step.y += 2.0*_height )
        {
            Mesh( step );
        }
    }
}

void Background::VertexColor( Vector2d& p )
{
    glColor3f( _brightness * _generator->GetValue( p, _red_offset ),
               _brightness * _generator->GetValue( p, _green_offset ),
               _brightness * _generator->GetValue( p, _blue_offset ) );

}

void Background::Mesh( Vector2d& p1 )
{
    Vector2d p2(p1.x + _halfSide, p1.y + _height);
    Vector2d p3(p1.x, p1.y + _height * 2.0);

    Triangle( p1 );
    Triangle( p2 );
    ReverseTriangle( p3 );
    ReverseTriangle( p2 ); 
}

void Background::Triangle( Vector2d& A )
{
    Vector2d B(A.x + _halfSide, A.y + _height);
    Vector2d C(A.x + _size, A.y);

    if ( _wireframe )
    {
        glColor3d( WIRE_COLOR, WIRE_COLOR, WIRE_COLOR );
        glBegin( GL_LINE_LOOP );
        glVertex3d( A.x, A.y, 0.0 );
        glVertex3d( B.x, B.y, 0.0 );
        glVertex3d( C.x, C.y, 0.0 );
        glEnd();
    }
    else
    {
        glBegin( GL_TRIANGLES );
        VertexColor( A );
        glVertex3d( A.x, A.y, 0.0 );
        VertexColor( B );
        glVertex3d( B.x, B.y, 0.0 );
        VertexColor( C );
        glVertex3d( C.x, C.y, 0.0 );
        glEnd();
    }

    // Increment vertex count by 3, for each triangle.
    _vertexCount += 3;
}

void Background::ReverseTriangle( Vector2d& A )
{
    Vector2d B(A.x + _size, A.y);
    Vector2d C(A.x + _halfSide, A.y - _height);

    if ( _wireframe )
    {
        glColor3d( WIRE_COLOR, WIRE_COLOR, WIRE_COLOR );
        glBegin( GL_LINE_LOOP );
        glVertex3d( A.x, A.y, 0.0 );
        glVertex3d( B.x, B.y, 0.0 );
        glVertex3d( C.x, C.y, 0.0 );
        glEnd();
    }
    else
    {
        glBegin( GL_TRIANGLES );
        VertexColor( A );
        glVertex3d( A.x, A.y, 0.0 );
        VertexColor( B );
        glVertex3d( B.x, B.y, 0.0 );
        VertexColor( C );
        glVertex3d( C.x, C.y, 0.0 );
        glEnd();
    }

    // Increment vertex count by 3, for each triangle.
    _vertexCount += 3;
}
