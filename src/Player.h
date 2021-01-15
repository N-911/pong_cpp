#ifndef PONG_SRC_PLAYER_H_
#define PONG_SRC_PLAYER_H_
#include "GameObjects.h"
#include "IObserver.h"

class Player : public  GameObject<SDL_Rect>, public IObserver {
public:

    Player();
    virtual ~Player() override;

    void UpdateStatus(Uint32 event) override;

    void moveUp();
    void moveDown();
    void stop();

};

#endif //PONG_SRC_PLAYER_H_
