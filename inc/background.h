#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <vector.h>
#include <definitions.h>
#include <layer.h>

class BackgroundLayer : public Layer
{
    public:
        BackgroundLayer();
        ~BackgroundLayer();
        bool Init( Volume& viewport );
        void Render();
        void Toggle();
        void ToggleWireframe();
        void ProcessCommand( Command* cmdCode );

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

