#ifndef PONG_SRC_SETTINGS_H_
#define PONG_SRC_SETTINGS_H_

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#define FPS 40
#define W 840
#define H 600
#define BALL_SIZE (16)
#define PLAYER_H (32)
#define PLAYER_W (32)
#define FONT_SIZE 32
#define SCORE_BOURD_X (W / 2 + FONT_SIZE)
#define SCORE_BOURD_Y (FONT_SIZE * 2)

enum POSITION {
  LEFT = 0,
  RIGHT = 1
};

struct Vec2i {
  int x;
  int y;
};

struct Vec2f {
  float x;
  float y;
};

struct Circle {
  int x;
  int y;
  int r;
};

struct Vec2d {
  int x;
  int y;
};

#endif //PONG_SRC_SETTINGS_H_
