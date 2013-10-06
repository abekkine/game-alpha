#ifndef MENU_H
#define MENU_H

#include <layer.h>

class Menu : public Layer
{
    public:
        Menu();
        ~Menu();
        bool Init( Volume& viewport );
        void Render();
        void ProcessCommand( Event::CommandType cmdCode );

    private:
        void Defaults();
        void RenderOptions();

};

#endif

