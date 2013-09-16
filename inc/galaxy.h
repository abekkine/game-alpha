#ifndef GALAXY_H
#define GALAXY_H

#include <definitions.h>
#include <layer.h>
#include <starbuilder.h>

class Galaxy : public Layer
{
    public:
        Galaxy();
        ~Galaxy();
        bool Init( Volume& viewport );
        void Render();
        void Toggle();
        void ToggleWireframe();

    private:
        // Methods.
        void Defaults();
        void RenderGalaxyLayer();

    private:
        // Member.
        StarBuilder* _starbuilder;

        bool _visible;
        bool _wireframe;
        double _step_delta;
};

#endif
