#ifndef PONG_SRC_PLAYER_H_
#define PONG_SRC_PLAYER_H_
#include "GameObjects.h"
#include "IObserver.h"
#include "EventManager.h"

class Player :
        public GameObject, public IObserver {

public:
    Player(EventManager& observable, int side);
    virtual ~Player() override;

    void update_status(SDL_Event& event) override;

    void move() override;
    Vec2i check_colision(Circle ball)  const override;

private:
    EventManager& m_observer;
    const int m_side;
    int m_current_id;

    void process_event(SDL_Event& event);
    void move_up();
    void move_down();
    void stop();
};

#endif //PONG_SRC_PLAYER_H_
