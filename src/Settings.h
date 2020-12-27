#pragma once

#ifndef PONG_SRC_SETTINGS_H_
#define PONG_SRC_SETTINGS_H_

#define FPS 40
#define W 840
#define H 600
#define WIDTH 840
#define HEIGHT 600
#define BRAKING 0.991
#define SIZE_BALL (16)
#define PLAYER_H (60)
#define PLAYER_W (16)

enum POSITION {
  LEFT = 0,
  RIGHT = 1
};


/*
struct Manifold
{
  Object *A;
  Object *B;
  float penetration;
  Vec2 normal;
};

*/

struct Vec2i
{
  int x;
  int y;
};

struct Vec2f
{
  float x;
  float y;
};

struct Box
{
  Vec2i min;  // верхний левый угол
  Vec2i max;  // нижний правый угол
};


struct Circle
{
  float radius;
  Vec2i position;
};

#endif //PONG_SRC_SETTINGS_H_
