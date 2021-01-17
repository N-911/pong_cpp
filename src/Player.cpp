#include "Player.h"
#include "Window.h"
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

Player::Player(EventManager& observable, int side)
        :m_observer(observable), m_side(side)
{
    m_observer.Attach(this);
    cout << "Attach Player to observer id =" << ++m_observer_id << endl;
    this->m_current_id = m_observer_id;
    m_speed = 10;  // speed player moving up or down
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

void Player::UpdateStatus(SDL_Event& event)
{
    cout << "Player::UpdateStatus side = " << m_side << endl;
    process_event(event);
    move();
    check_move();
//    moving();
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
            /*
             if (m_side == 1) {
                 if (event.key.keysym.sym == SDLK_UP) {
                     stop();
                 }
                 else if (event.key.keysym.sym == SDLK_DOWN) {
                     stop();
                 }
             }
             else if (m_side == 0) {
                 if (event.key.keysym.sym == SDLK_w) {
                     stop();
                 }
                 else if (event.key.keysym.sym == SDLK_s) {
                     stop();
                 }
             }
             break;
             }
             */
/*
        case (SDL_KEYDOWN) : {
            if (m_side == 0 && event.key.keysym.sym == SDLK_DOWN) {
                set_move(event.key.keysym.sym);
            }
            if (m_side == 0 && (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_s)) {
                set_move(event.key.keysym.sym);
            }
            break;
        }
        case (SDL_KEYUP) : {
            if (m_side == 1 && (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN)) {
                disable_move(event.key.keysym.sym);
            }
            if (m_side == 0 && (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_s)) {
                disable_move(event.key.keysym.sym);
            }
            break;
        }
    */
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

void Player::check_move()
{
    if (m_y < 0) {
        m_y = 0;
        update_box();
        stop();
    }
    if (m_y > H - PLAYER_H) {
        m_y = H - PLAYER_H;
        stop();
        update_box();
    }
}




//foo() {
//    //                set_move(event.key.keysym.sym);
//    if (m_side == 0 && event.key.keysym.sym == SDLK_DOWN) {
//        move_up();
//    }
//    if (m_side == 0 && (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_s)) {
//        move_up();
//        set_move(event.key.keysym.sym);
//    }
//}
/*
void foo()
{
    switch (event.type) {
        case SDL_QUIT:m_loop = SDL_FALSE;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                m_loop = SDL_FALSE;
                break;
            }
            if (event.key.keysym.sym == SDLK_SPACE) {
                m_pause = !m_pause;
                break;
            }

            if (event.key.keysym.sym == SDLK_p) {  // new ball for testing
//        m_ball->set_new_ball(1);
//        m_ball->moving();
            }
            if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN ||
                    event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT) {
                m_left->set_move(event.key.keysym.sym);
            }
            if (m_number_pl == 2) {
                if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_s ||
                        event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_a) {
                    m_right->set_move(event.key.keysym.sym);
                }
            }
            break;
        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN ||
                    event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT) {
                m_left->disable_move(event.key.keysym.sym);
            }
            if (m_number_pl == 2) {
                if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_s ||
                        event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_a) {
                    m_right->disable_move(event.key.keysym.sym);
                }
            }
            break;
        default:m_loop = SDL_TRUE;
    }
*/