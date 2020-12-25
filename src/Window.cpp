//
// Created by snikolayen on 25.12.2020.
//
#include "Window.h"
#include "iostream"

using std::cout;
using std::endl;

Window::Window() {
  cout << "Window Construtor" << endl;
  init_SDL();
  create_window();
  setup_window_icon();

  m_surface = IMG_Load("resources/floor.png");
  if (m_surface == NULL) {
    cout << "[Error] Unable to load image : " << SDL_GetError() << endl;
    exit(0);
  }
  m_text_color = (SDL_Color){255, 255, 0, 255};
  m_pixels = (unsigned int *)m_surface->pixels;
}


Window::~Window() {
  cout << "Window destructor" << endl;
  TTF_CloseFont(m_shrift);
  TTF_Quit();

  Mix_FreeMusic(m_bum);
  Mix_FreeMusic(m_goal);
  Mix_CloseAudio();

  SDL_DestroyTexture(m_texture);
  SDL_DestroyRenderer(m_render);
  SDL_FreeSurface(m_surface);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

void Window::init_SDL() {

  // Initialise SDL2 and output some useful display info
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    cout << "[Error] SDL Init : " << SDL_GetError() << endl;
    exit(1);
  } else {
    cout << "SDL INITIALISED\n";
    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);
    cout << "Display mode is "<< dm.w << "x" << dm.h << "px @ " << dm.refresh_rate << "hz\n";
  }

  // Initialise TTF
  if (TTF_Init() == -1)
  {
    cout << TTF_GetError() << endl;
    exit(1);
  }
  m_shrift = TTF_OpenFont("resources/OpenSans-Regular.ttf", 40);
  if (!m_shrift)
  {
    cout << TTF_GetError() << endl;
    exit(1);
  }

  // Initialise mixer
  if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != 0) {
    cout << "[Error] Error Initialising Audio : "  << Mix_GetError() << endl;
    exit(1);
  } else {
    cout << "Audio Initialised\n";
  }
  m_bum = Mix_LoadMUS("resources/bum.wav");
  m_goal = Mix_LoadMUS("resources/goal.wav");
}


void Window::create_window()
{
  if (!(m_window = SDL_CreateWindow("PONG", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN |
          SDL_WINDOW_OPENGL)))
  {
    cout << SDL_GetError() << endl;
    exit(1);
  } else {
    cout << "Created Window and Renderer " << WIDTH << "x" << HEIGHT << endl;
  }
  if (!(m_render = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED)))
  {
    cout << SDL_GetError() << endl;
    exit(1);
  }
  if (!(m_texture = SDL_CreateTexture(m_render, SDL_PIXELFORMAT_ARGB8888,
                                    SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT)))
  {
    cout << SDL_GetError() << endl;
    exit(1);
  }
}

void Window::setup_window_icon()
{
  SDL_Surface *iconSurface;
  iconSurface = IMG_Load("resources/pong_icon.png");

  // The icon requires the window pointer NOT the renderer
  SDL_SetWindowIcon(m_window, iconSurface);

  // ...and can now free the appicon surface
  SDL_FreeSurface(iconSurface);
}

void Window::draw_surface(unsigned int *color) const {
  for (int i = 0; i < W; i++)
  {
    for (int j = 0; j < H; j++)
    {
      color[i + j * WIDTH] = m_pixels[i + j * W];
    }
  }
}