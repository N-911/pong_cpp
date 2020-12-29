#ifndef PONG_SRC_WINDOW_H_
#define PONG_SRC_WINDOW_H_

// #include <SDL.h>
// #include <SDL_ttf.h>
// #include <SDL_image.h>
// #include <SDL_mixer.h>
#include "Settings.h"

class Window {

 public:
  Window();
  virtual ~Window();

  TTF_Font *getShrift() const { return m_shrift; }
  SDL_Renderer *getRender() const {return m_renderer; }
  SDL_Texture *getTexture() {return m_texture;}
 private:
  SDL_Window *m_window;
  SDL_Surface *m_surface;
  TTF_Font *m_shrift;
  SDL_Renderer *m_renderer;
  SDL_Texture *m_texture;
  SDL_Color m_text_color;
  Mix_Music	*m_bum;
  Mix_Music	*m_goal;

  void init_SDL();
  void create_window();
  void init_window_and_renderer();
  void setup_window_icon();

};

#endif //PONG_SRC_WINDOW_H_
