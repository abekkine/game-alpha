#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL/SDL.h>
#include <GL/gl.h>

#include <definitions.h>
#include <timer.h>
#include <writer.h>
#include <menu.h>
#include <event.h>
#include <background.h>
#include <galaxy.h>

//! @brief Class responsible for rendering objects.
class Display
{
    public:
        //! @brief Constructor.
        Display();
        //! @brief Destructor.
        ~Display();
        //! @brief Initialization method.
        bool Init();
        //! @brief Update method.
        void Update();

    private:
        // Methods
        void Defaults();
        bool InitGL();
        bool InitComponents();
        void Render();
        bool CheckError();
        void Reshape();
        void Reshape( int width, int height );
        
        void ProcessCommands();
        void ProcessEvents();
        void ToggleWireframe();

    private:
        // Components.

        // Display menu.
        Menu* _menu;

        // User events.
        Event* _event;

        // Background layer.
        Background* _background;

        // Galaxy layer.
        Galaxy* _galaxy;

    private:
        // Members

        // Display surface.
        SDL_Surface* _screen;

        // Viewport
        Volume _viewport;

        // Viewport screen dimensions.
        int _screen_width;
        int _screen_height;

        // Clear color settings.
        float _clear_red;
        float _clear_green;
        float _clear_blue;
        float _clear_alpha;

        // Frames per second.
        double _fps;
        Timer* _fps_timer;
};

#endif

