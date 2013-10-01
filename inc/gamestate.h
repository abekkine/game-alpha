#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState
{
    public:
        typedef enum {
            gsMENU = 0,
            gsPLAY,
            gsPAUSE,
            gsGAMEOVER,
            gsQUIT
        } GameStateType;

    private:
        static GameState* _instance;
        GameState();

    public:
        static GameState* Instance();
        ~GameState();
        GameStateType State();
        void State(GameStateType state);

    private:
        GameStateType _state;
};

#endif

