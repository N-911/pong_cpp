#ifndef PONG_SRC_GAMEOBJECTS_H_
#define PONG_SRC_GAMEOBJECTS_H_

#include <memory>
#include "Settings.h"
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>

using std::cout;

class Ball;

template<typename T>
class GameObject {

public:
    // Constructors
    GameObject()
    {
        m_object = new T();

    }
    GameObject(GameObject& other) = delete;
    GameObject& operator=(GameObject& other) = delete;
    GameObject(GameObject&& other) = delete;
    GameObject& operator=(GameObject&& other) = delete;

    // Destructor
    ~GameObject()
    {
//        delete m_sampleRect;
        delete m_object;
    }

    Vec2i velocity() const { return m_velocity; }

    // modify
    void set_velocity(Vec2i v) { m_velocity = v; }
    void set_speed(int s) { m_speed = s; }
    void set_x(int n);
    void set_y(int n);

    void move();
    void update_box();

//  virtual void set_center();
    void set_move(int& key);
    virtual void moving();
    virtual void moving(std::shared_ptr<Ball> ball) { };
//  virtual void move_start();
    virtual void disable_move(int& key);
//  void check_colision(std::shared_ptr<Ball> m_ball);
    SDL_Rect* get_rect() { return m_object; }
//  Vec2i get_center() const { return center; }
//  Vec2f get_speed() const { return speed; }
//  double get_radius() const { return m_radius; }

protected:
    //  double m_radius;  // radius circle in AABB
//    SDL_Rect* m_sampleRect;

    bool m_move_up;
    bool m_move_down;
    bool m_move_left;
    bool m_move_right;
    Vec2i center;

    int m_speed{0};
    int m_x{0};
    int m_y{0};
    Vec2i m_velocity{0, 0};
    T* m_object;

};

template<typename T>
void GameObject<T>::move()
{
    m_x += m_velocity.x;
    m_y += m_velocity.y;
    update_box();
}

////////////////////////===========
template<typename T>
void GameObject<T>::set_x(int n)
{
    m_x = n;
    update_box();
}

template<typename T>
void GameObject<T>::set_y(int n)
{
    m_y = n;
    update_box();
}

template<typename T>
void GameObject<T>::set_move(int& key)
{

    switch (key) {
        case SDLK_UP:m_move_up = true;
            m_velocity.y = -m_speed;
            break;
        case SDLK_w:m_move_up = true;
            m_velocity.y = -m_speed;
            break;
        case SDLK_DOWN:m_move_down = true;
            m_velocity.y = m_speed;
            break;
        case SDLK_s:m_move_down = true;
            m_velocity.y = m_speed;
            break;
    }
}
template<typename T>
void GameObject<T>::disable_move(int& key)
{
    switch (key) {
        case SDLK_UP:m_move_up = false;
            m_velocity.y = 0;
            break;
        case SDLK_w:m_move_up = false;
            m_velocity.y = 0;
            break;
        case SDLK_DOWN:m_move_down = false;
            m_velocity.y = 0;
            break;
        case SDLK_s:m_move_down = false;
            m_velocity.y = 0;
            break;
    }
}
template<typename T>
void GameObject<T>::moving()
{
    cout << "moving  Player";
    if (m_move_up) {
        if (m_y - m_speed > 0)
            m_y -= m_speed;
        else
            m_y = 0;
    }
    if (m_move_down) {
        if (m_y + m_speed < H - PLAYER_H)
            m_y += m_speed;
        else
            m_y = H - PLAYER_H;
    }
    update_box();
//  set_center();
}

#endif //PONG_SRC_GAMEOBJECTS_H_
