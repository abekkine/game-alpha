#ifndef EVENT_H
#define EVENT_H

#include <queue>

#include <SDL/SDL.h>

#include <vector.h>

class Event
{
    public:
        // Command Definitions.
        enum CommandType {
            cmd_NONE = 0,
            cmd_TOGGLE_WIREFRAME,
            cmd_TOGGLE_BACKGROUND,
            cmd_TOGGLE_FOREGROUND,
            cmd_TOGGLE_PANEL,
            cmd_ZOOM,
            cmd_PAN,
            cmd_SELECT,
            cmd_UP,
            cmd_DOWN,
            cmd_LEFT_ENABLE,
            cmd_LEFT_DISABLE,
            cmd_RIGHT_ENABLE,
            cmd_RIGHT_DISABLE,
            cmd_FIRE
        };

    private:
        // Event Definitions.
        enum EventType {
            evt_NONE = 0,
            evt_LEFTBUTTON_PRESSED,
            evt_LEFTBUTTON_RELEASED,
            evt_RIGHTBUTTON_PRESSED,
            evt_RIGHTBUTTON_RELEASED,
            evt_MIDBUTTON_PRESSED,
            evt_MIDBUTTON_RELEASED
        };
        
        enum ButtonStateType {
             bs_UNDEFINED = 0,
             bs_PRESSED,
             bs_RELEASED
        };

    private:
        static Event* _instance;
        Event();

    public:
        static Event* Instance();
        ~Event();
        bool Init();
        bool Update();
        CommandType GetCommand();
        void GetMousePosition( Vector2i& mouse );
        
    private:
        // Methods.
        void Defaults();
        void Poll();
        void CommandProcess();
        void PanCommand();
        void PanUpdate();
        void WheelZoom( SDL_MouseButtonEvent& button );
        void LimitZoom();
        void ZoomCommand();
        void ZoomUpdate();
        void KeyEvent( SDL_KeyboardEvent& key, int state );
        void MotionEvent( SDL_MouseMotionEvent& motion );
        void ButtonEvent( SDL_MouseButtonEvent& button );
        void ProcessLeftButton( SDL_MouseButtonEvent& button );
        void ProcessMiddleButton( SDL_MouseButtonEvent& button );
        void ProcessRightButton( SDL_MouseButtonEvent& button );
        void QuitEvent();
        void PanMode( bool value );
        void ZoomMode( bool value );
        void PushCommand( CommandType code );
        void PushEvent( EventType code );
        EventType PopEvent();

    public:
        static int _zoom_delta;
        static Vector2i _pan_delta;

        static bool _quit_condition;

    private:
        // Members.
        Vector2i _mouse;

        bool _pan_mode;
        bool _zoom_mode;
        int _speed_factor;
        Vector2i _pan_start;
        Vector2i _zoom_start;
        int _zoom_total;

        std::queue< EventType > _event_queue;
        std::queue< CommandType > _command_queue;
};

#endif

