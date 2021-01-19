#ifndef PONG_SRC_BALL_H_
#define PONG_SRC_BALL_H_

#include "GameObjects.h"
#include <random>

class Ball : public GameObject {

public:
    Ball() = default;
    Ball(int x, int y);

    virtual ~Ball() { }
    void move() override;
    Vec2i check_colision(Circle ball) override;

    void set_rand_velocity();
    void set_new_ball(int side);

    Circle get_ball_geomerty() const;

private:
    int m_radius;
    std::mt19937 m_mt;
    std::random_device m_rdevice;

    void update_box() override;

};


/*
void moving();
bool is_movind() const;
SDL_Rect *get_rect() const { return m_sampleRect; }
Vec2i get_center() const { return center;` }
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
