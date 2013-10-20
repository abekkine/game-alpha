#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState
{
    public:
        typedef enum {
            gsMENU = 0,
            gsINIT,
            gsPLAY,
            gsPAUSE,
            gsGAMEOVER,
            gsQUIT
        } GameStateType;

    private:
        static GameState* _instance;
        GameState();
        void Dump();

    public:
        static GameState* Instance();
        ~GameState();

        GameStateType State();
        void State(GameStateType state);

        double Health();
        void Health(double health);

        int Score();
        void Score(int score);

    private:
        GameStateType _state;
        double _health;
        int _score;
};

#endif

