#include "Game.h"
#include <iostream>

using std::cout;
using std::endl;

Game::Game() {
  cout << "Game Constructor" << endl;

  m_close = false;
  m_number_pl = showMenu();

//  NUM_PLAYERS = showmenu();

}

Game::~Game() {

}
int Game::showMenu()  {
  SDL_Surface *screen = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
  SDL_Texture *texture;

  int x, y;
  const int NUMMENU = 2;
  const char *menu_point[NUMMENU] = {"Single Player", "Multiplayer"};
  bool selected[NUMMENU] = {0, 0};
  SDL_Color color[2] = {{255, 255, 255, 0}, {255, 0, 0, 0}};

  SDL_Surface *menus[NUMMENU];

  menus[0] = TTF_RenderText_Solid(m_window.getShrift(), menu_point[0], color[0]);
  menus[1] = TTF_RenderText_Solid(m_window.getShrift(), menu_point[1], color[0]);

  SDL_Rect pos[NUMMENU];

  pos[0].x = screen->clip_rect.w / 2 - menus[0]->clip_rect.w / 2;
  pos[0].y = screen->clip_rect.h / 2 - menus[0]->clip_rect.h;
  pos[1].x = screen->clip_rect.w / 2 - menus[0]->clip_rect.w / 2;
  pos[1].y = screen->clip_rect.h / 2 + menus[0]->clip_rect.h;

  SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));

  while (1) {
    while (SDL_PollEvent(&m_ev)) {
      switch (m_ev.type) {
        case SDL_QUIT:SDL_FreeSurface(menus[0]);
          SDL_FreeSurface(menus[1]);
          SDL_FreeSurface(screen);
          SDL_DestroyTexture(texture);
          m_close = true;
          return (0);

        case SDL_KEYDOWN:
          if (m_ev.key.keysym.sym == SDLK_ESCAPE) {
            SDL_FreeSurface(menus[0]);
            SDL_FreeSurface(menus[1]);
            SDL_FreeSurface(screen);
            SDL_DestroyTexture(texture);
            m_close = true;
            return (0);
          }

        case SDL_MOUSEMOTION:x = m_ev.motion.x;
          y = m_ev.motion.y;
          for (int i = 0; i < NUMMENU; i += 1) {
            if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                y >= pos[i].y && y <= pos[i].y + pos[i].h) {
              if (!selected[i]) {
                selected[i] = 1;
                SDL_FreeSurface(menus[i]);
                menus[i] = TTF_RenderText_Solid(m_window.getShrift(), menu_point[i], color[1]);
              }
            } else {
              if (selected[i]) {
                selected[i] = 0;
                SDL_FreeSurface(menus[i]);
                menus[i] = TTF_RenderText_Solid(m_window.getShrift(), menu_point[i], color[0]);
              }
            }
          }
          break;

        case SDL_MOUSEBUTTONDOWN:x = m_ev.button.x;
          y = m_ev.button.y;
          for (int i = 0; i < NUMMENU; i += 1) {
            if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                y >= pos[i].y && y <= pos[i].y + pos[i].h) {
              SDL_FreeSurface(screen);
              SDL_DestroyTexture(texture);
              SDL_FreeSurface(menus[0]);
              SDL_FreeSurface(menus[1]);
              return (i + 1);
            }
          }
          break;
      }
    }

    for (int i = 0; i < NUMMENU; i += 1) {
      SDL_BlitSurface(menus[i], NULL, screen, &pos[i]);
    }

    texture = SDL_CreateTextureFromSurface(m_window.getRender(), screen);

    SDL_Rect rect;

    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    rect.x = (WIDTH - rect.w) / 2;
    rect.y = (HEIGHT - rect.h) / 2;

    SDL_RenderClear(m_window.getRender());
    SDL_RenderCopy(m_window.getRender(), texture, NULL, &rect);
    SDL_RenderPresent(m_window.getRender());
  }
}
