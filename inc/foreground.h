#ifndef GALAXY_H
#define GALAXY_H

#include <definitions.h>
#include <layer.h>
#include <event.h>

class ForegroundLayer : public Layer
{
    public:
        ForegroundLayer();
        ~ForegroundLayer();
        bool Init( Volume& viewport );
        void Render();
        void Toggle();
        void ToggleWireframe();
        void ProcessCommand( Command* cmd );

    private:
        // Methods.
        void Defaults();
        void RenderForegroundLayer();

        void RenderGround();

    private:
        // Member.
        bool _visible;
        bool _wireframe;
};

#endif
