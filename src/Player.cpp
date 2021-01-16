#include "Player.h"
#include "Window.h"
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

Player::Player(EventManager& observable)
        :m_observer(observable)
{
    m_observer.Attach(this);
    cout << "Attach Player to observer id =" << ++m_observer_id << endl;
    this->m_current_id = m_observer_id;
    m_object->x = 10;
    m_object->y = H / 2 - 5;
}

Player::~Player()
{

}

void Player::UpdateStatus(SDL_Event& event)
{
    switch (event.type) {
        case (SDL_KEYDOWN) : {
            if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN) {
                set_move(event.key.keysym.sym);
            }
            if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_s) {
                set_move(event.key.keysym.sym);
            }
        }
        case(SDL_KEYUP) : {
            if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN) {
                disable_move(event.key.keysym.sym);
            }
            if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_s) {
                disable_move(event.key.keysym.sym);
            }
        }
    }
}


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