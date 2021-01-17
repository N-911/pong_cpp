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
        delete m_object;
    }

    // get
    Vec2i velocity() const { return m_velocity; }
    SDL_Rect* get_rect() { return m_object; }

    // modify
    void set_velocity(Vec2i v) { m_velocity = v; }
    void set_speed(int s) { m_speed = s; }
    void set_x(int n);
    void set_y(int n);
    void move();

//    virtual void moving();
//    virtual void moving(std::shared_ptr<Ball> ball) { };
//  virtual void move_start();
//  void check_colision(std::shared_ptr<Ball> m_ball);

protected:
    int m_speed{0};
    int m_x{0};
    int m_y{0};
    Vec2i m_velocity{0, 0};
    T* m_object;

    void update_box();
};

template<typename T>
void GameObject<T>::move()
{
    m_x += m_velocity.x;
    m_y += m_velocity.y;
    update_box();
}

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

#endif //PONG_SRC_GAMEOBJECTS_H_
