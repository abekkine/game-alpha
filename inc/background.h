#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <vector.h>
#include <definitions.h>
#include <generator.h>
#include <layer.h>

class Background : public Layer
{
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

    private:
        // Members.
        bool _visible;
        bool _wireframe;
};

#endif

