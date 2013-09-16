#ifndef GALAXY_H
#define GALAXY_H

#include <definitions.h>
#include <layer.h>

class Foreground : public Layer
{
    public:
        Foreground();
        ~Foreground();
        bool Init( Volume& viewport );
        void Render();
        void Toggle();
        void ToggleWireframe();

    private:
        // Methods.
        void Defaults();
        void RenderForegroundLayer();

    private:
        // Member.
        bool _visible;
        bool _wireframe;
};

#endif
