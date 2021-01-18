#ifndef PONG_SRC_GAMEOBJECTS_H_
#define PONG_SRC_GAMEOBJECTS_H_

#include <memory>
#include "Settings.h"
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>

using std::cout;

class Ball;

class GameObject {

public:
    // Constructors
    GameObject();
    GameObject(GameObject& other) = delete;
    GameObject& operator=(GameObject& other) = delete;
    GameObject(GameObject&& other) = delete;
    GameObject& operator=(GameObject&& other) = delete;

    ~GameObject() = default;

    // get
    Vec2i velocity() const { return m_velocity; }
    SDL_Rect* get_rect() { return m_object; }

    // modify
    void set_velocity(Vec2i v) { m_velocity = v; }
    void set_speed(int s) { m_speed = s; }
    void set_x(int n);
    void set_y(int n);
    virtual void move() = 0;

//    virtual void moving();
//    virtual void moving(std::shared_ptr<Ball> ball) { };
//  virtual void move_start();
//  void check_colision(std::shared_ptr<Ball> m_ball);

protected:
    int m_speed{0};
    int m_x{0};
    int m_y{0};
    Vec2i m_velocity{0, 0};
    SDL_Rect* m_object;

    void update_box();
};


#endif //PONG_SRC_GAMEOBJECTS_H_
