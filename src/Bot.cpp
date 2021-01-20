#include "Bot.h"
#include <iostream>

using std::cout;
using std::endl;

Bot::Bot(int side) : m_side(side) { };

void Bot::move(Circle ball)
{
    if (ball.x < 0) {
        return;
    }
    if (ball.x < H / 2) {
        return;
    }
    else if (ball.y + PLAYER_H / 4 > (m_y - PLAYER_H / 2)) {
        m_y += (m_speed + 3);
    }
    else {
        m_y -= (m_speed + 3);
    }
    update_box();
}

Vec2i Bot::check_colision(Circle ball) const
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
