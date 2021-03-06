#ifndef LAYER_H
#define LAYER_H

#include <vector.h>
#include <definitions.h>
#include <command.h>

class Layer
{
    public:
        Layer();
        virtual ~Layer() = 0;

    // Interface
    public:
        virtual void ProcessCommand( Command* cmd ) = 0;

    protected:
        void PreRender();
        void PostRender();

    private:
        void Defaults();
        void UpdateViewport();

    public:
        bool Init(Volume& viewport);
        void Resize(int width, int height);

    protected:
        bool _use_screen_coords;
        Volume _viewport; 
        double _zoom_factor;
        double _pan_factor;

    private:

        double _zoom_level;
        Vector2d _scale;
        Vector2d _center;
};

#endif
