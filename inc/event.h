#ifndef EVENT_H
#define EVENT_H

#include <queue>

#include <SDL/SDL.h>

#include <vector.h>

class Event
{
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
        void GetMousePosition( Vector2i& mouse );
        
    private:
        // Methods.
        void Defaults();
        void Poll();
        void Process();
        void PanUpdate();
        void WheelZoom( SDL_MouseButtonEvent& button );
        void LimitZoom();
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
        void PushEvent( EventType code );
        EventType PopEvent();

    public:
        static int _zoom_delta;
        static Vector2i _pan_delta;

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
};

#endif

