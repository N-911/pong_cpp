#ifndef PONG_SRC_BALL_H_
#define PONG_SRC_BALL_H_

#include "GameObjects.h"

class Ball : public GameObject {

public:
    Ball() = default;
    Ball(int x, int y);

    virtual ~Ball() { }
    void move() override;
    void set_new_ball(int side);
private:

};


/*
void moving();
bool is_movind() const;
SDL_Rect *get_rect() const { return m_sampleRect; }
Vec2i get_center() const { return center; }
Vec2f get_speed() const { return speed; }
double get_radius() const { return m_radius; }
void set_new_ball(int side);

void set_center();
void set_rect_x(int x);
void set_rect_y(int y);
void set_speed_x(int x);
void set_speed_y(int y);

 */

#endif //PONG_SRC_BALL_H_
