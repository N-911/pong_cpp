#ifndef PONG_SRC_PLAYER_H_
#define PONG_SRC_PLAYER_H_
#include "GameObjects.h"
#include "IObserver.h"
#include "EventManager.h"

class Player : public  GameObject<SDL_Rect>, public IObserver {
public:

//    Player();
    Player(EventManager& observable);
    virtual ~Player() override;

    void UpdateStatus(SDL_Event& event) override;

    void moveUp();
    void moveDown();
    void stop();

private:
//    SDL_Event* m_event_key {nullptr};
    EventManager  &m_observable;
//    const int    m_id;
    int   m_current_id;
};

#endif //PONG_SRC_PLAYER_H_
