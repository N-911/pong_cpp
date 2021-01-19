#include "Game.h"
#include "IObserver.h"

int IObserver::m_observer_id = 0;

int main()
{

    Game game;
    game.game_loop();
//  system ("leaks -q pong");
    return (0);
}
