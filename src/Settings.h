#pragma once

#ifndef PONG_SRC_SETTINGS_H_
#define PONG_SRC_SETTINGS_H_

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"


#define FPS 40
#define W 840
#define H 600
#define BRAKING 0.991
#define BALL_SIZE (16)
#define PLAYER_H (60)
#define PLAYER_W (16)
#define FONT_SIZE 32
#define BALL_SPEED 22

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


struct Circle {
  int x;
  int y;
  int r;
};

#endif //PONG_SRC_SETTINGS_H_
