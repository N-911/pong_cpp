//
// Created by snikolayen on 25.12.2020.
//

#ifndef PONG_SRC_WINDOW_H_
#define PONG_SRC_WINDOW_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#define FPS 40
#define W 480
#define H 720
#define WIDTH 480
#define HEIGHT 720
#define BRAKING 0.991

class Window {
 public:
  Window();
  virtual ~Window();

  void draw_surface(unsigned int *color) const;
  TTF_Font *getShrift() const { return m_shrift; }
  SDL_Renderer *getRender() const {return m_render; }

 private:
  SDL_Window *m_window;
  SDL_Surface *m_surface;
  unsigned int *m_pixels;

  TTF_Font *m_shrift;
  SDL_Renderer *m_render;
  SDL_Texture *m_texture;
  SDL_Color m_text_color;
  Mix_Music	*m_bum;
  Mix_Music	*m_goal;

  void init_SDL();
  void create_window();
  void setup_window_icon();

};

#endif //PONG_SRC_WINDOW_H_
