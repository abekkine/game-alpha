#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <vector.h>
#include <definitions.h>
#include <generator.h>
#include <layer.h>

class Background : public Layer
{
    private:
        const double INTERIOR_ANGLE;
        const double WIRE_COLOR;

    public:
        Background();
        ~Background();
        bool Init( Volume& viewport );
        void Render();
        void Toggle();
        void ToggleWireframe();

    private:
        // Methods.
        void Defaults();
        void RenderBackground();

        void VertexColor( Vector2d& p );
        void Triangle( Vector2d& A );
        void ReverseTriangle( Vector2d& A );
        void Mesh( Vector2d& p1 );

    private:
        // Members.
        Generator* _generator;

        bool _visible;
        int _vertexCount;
        bool _wireframe;
        float _size_initial;
        float _size;
        float _height;
        float _halfSide;
        float _brightness;
        float _red_offset;
        float _green_offset;
        float _blue_offset;
};

#endif

