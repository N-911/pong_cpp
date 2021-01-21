#ifndef PONG_SRC_BOT_H_
#define PONG_SRC_BOT_H_

#include "GameObjects.h"

class Ball;

class Bot : public GameObject {

public:
    Bot(int side);
    virtual ~Bot() { }

    void move() override {};
    void move(Circle ball) ;
    Vec2i check_colision(Circle ball) const override;
//    void moving() override { };
private:
    const int m_side;

};

#endif //PONG_SRC_BOT_H_
