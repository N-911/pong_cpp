#include "Player.h"
#include "Window.h"
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

Player::Player(EventManager& observable, int side)
        :m_observer(observable), m_side(side)
{
    m_observer.attach(this);
    cout << "Attach Player to observer id =" << ++m_observer_id << endl;
    this->m_current_id = m_observer_id;
    m_speed = 12;  // speed player moving up or down
    if (m_side == 0) {
        m_x = 0;
    }
    else if (m_side == 1) {
        m_x = W - PLAYER_W;
    }
    m_y = H / 2 - PLAYER_H / 2;
    update_box();
    m_object->w = PLAYER_W;
    m_object->h = PLAYER_H;
}

Player::~Player()
{

}

void Player::update_status(SDL_Event& event)
{
    cout << "Player::UpdateStatus side = " << m_side << endl;
    process_event(event);
    move();
//    check_move();
}

void Player::process_event(SDL_Event& event)
{
    switch (event.type) {

        case (SDL_KEYDOWN) : {
            if (m_side == 1) {
                if (event.key.keysym.sym == SDLK_UP) {
                    move_up();
                }
                else if (event.key.keysym.sym == SDLK_DOWN) {
                    move_down();
                }
            }
            else if (m_side == 0) {
                if (event.key.keysym.sym == SDLK_w) {
                    move_up();
                }
                else if (event.key.keysym.sym == SDLK_s) {
                    move_down();
                }
            }
            break;
        }
        case (SDL_KEYUP) : {
            if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN ||
                    event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_s) {
                stop();
            }
            break;
        }
    }
}

void Player::move_up()
{
    set_velocity(Vec2i{0, -m_speed});
}

void Player::move_down()
{
    set_velocity(Vec2i{0, m_speed});
}

void Player::stop()
{
    set_velocity(Vec2i{0, 0});
}


void Player::move()
{
    m_x += m_velocity.x;
    m_y += m_velocity.y;

    if (m_y < 0) {
        m_y = 0;
//        update_box();
        stop();
    }
    if (m_y > H - PLAYER_H) {
        m_y = H - PLAYER_H;
//        update_box();
        stop();
    }
    update_box();
}

Vec2i Player::check_colision(Circle ball) const
{
//    cout << "m_x = " << m_x << " m_y = " << m_y << endl;
//    cout << "ball x = " << ball.x << " ball y = " << ball.y << endl;
    int col_x = -1;
    int col_y = -1;

    if (ball.y > m_y + PLAYER_H) {
        col_y = m_y + PLAYER_H;
    }
    else if (ball.y < m_y) {
        col_y = m_y;
    }
    else
        col_y = ball.y;

    if (ball.x > m_x + PLAYER_W)
        col_x = m_x + PLAYER_W;
    else if (ball.x < m_x) {
        col_x = m_x;
    }
    else {
        col_x = ball.x;
    }
    int distance = square_of_distance(ball.x, ball.y, col_x, col_y);

//    cout << "col  x = "  << col_x << " col y =" << col_y << endl;

    if (distance <  ball.r * ball.r) {
        cout << "distance = " << distance << endl;
        return {col_x, col_y};
    }
    else {
        return {-1, -1};
    }
}

int Player::square_of_distance(int x1, int y1, int x2, int y2) const
{
    return static_cast<int>(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}


//void Player::check_move()
//{
//    if (m_y < 0) {
//        m_y = 0;
//        update_box();
//        stop();
//    }
//    if (m_y > H - PLAYER_H) {
//        m_y = H - PLAYER_H;
//        update_box();
//        stop();
//    }
//}