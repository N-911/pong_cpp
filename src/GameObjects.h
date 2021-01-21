#ifndef PONG_SRC_GAMEOBJECTS_H_
#define PONG_SRC_GAMEOBJECTS_H_

#include <memory>
#include "Settings.h"
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>

using std::cout;

class GameObject {

public:
    // Constructors
    GameObject();
    GameObject(GameObject& other) = delete;
    GameObject& operator=(GameObject& other) = delete;
    GameObject(GameObject&& other) = delete;
    GameObject& operator=(GameObject&& other) = delete;

    virtual ~GameObject() = default;

    // get
    Vec2i velocity() const { return m_velocity; }
    SDL_Rect* get_rect() { return m_object; }

    // modify
    void set_velocity(Vec2i v) { m_velocity = v; }
    void set_x(int n);
    void set_y(int n);

    virtual void move() = 0;
    void move(Circle ball);

    virtual Vec2i check_colision(Circle ball) const = 0;

protected:
    int m_speed{0};
    int m_x{0};
    int m_y{0};
    Vec2i m_velocity{0, 0};
    SDL_Rect* m_object;

    virtual void update_box();
    int square_of_distance(int x1, int y1, int x2, int y2) const;
};

#endif //PONG_SRC_GAMEOBJECTS_H_
