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

//    void check_move();
    void move_up();
    void move_down();
    void stop();
    void move() override;

    Vec2i check_colision(Circle ball) override;

private:
    EventManager& m_observer;
    const int m_side;
    int m_current_id;

    void process_event(SDL_Event& event);
    int square_of_distance(int x1, int y1, int x2, int y2);
};

#endif //PONG_SRC_PLAYER_H_
