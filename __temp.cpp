
main



/*
  // SDL Inits
  init_sdl();
  init_window_and_renderer();
  init_ttf();
  init_audio();

  // Important note. These setup calls require the resources folder to be copied to the
  // bin folder. This is done via the CMakeList.txt file - see the 'file' call towards
  // the end. This means any changes to the resources after the initial project load
  // require the CMake project to be reloaded - in CLion use File -> Reload CMake Project

  // Setup a sample app icon
  setup_window_icon();

  // Setup a sample text header that we can draw later
  setup_header_text();

  // Setup a sample image
  setup_texture();

  // Play an audio file
//  play_audio();

  // Run our main game loop
  main_loop();

  // When we exit the loop clean up and exit SDL
  // Audio
  if (Mix_PlayingMusic()) {
    Mix_HaltMusic();
  }
  Mix_FreeMusic(_music);
  Mix_CloseAudio();
  // Images
  SDL_DestroyTexture(_headerText);
  SDL_DestroyTexture(_image);
  // TTF
  TTF_CloseFont(_font);
  TTF_Quit();
  // Window
  SDL_DestroyWindow(_window);
  // SDL
  SDL_Quit();
  exit(0);
}
 */

// SDL Window
SDL_Window *_window;

// SDL Renderer to draw to
SDL_Renderer *_renderer;

// Our default font
TTF_Font *_font;

// Easy access to a useful color
SDL_Color white = {255, 255, 255};

// Window size
int _width = 480;
int _height = 640;

// Our sample header texture and where we're drawing our header to
SDL_Rect _headerTextRect;
SDL_Texture *_headerText;

// Our sample texture
SDL_Texture *_image;

// Our sample rectangle that we can drag around the viewport
SDL_Rect _sampleRect = {.x = 200, .y = 620, .w = 80, .h = 15};
SDL_bool _inSampleRect = SDL_FALSE;

// Our sample 'music'
Mix_Music *_music = NULL;

/**
 * Initialise SDL2 and output some useful display info
 */
void init_sdl()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    printf("[Error] SDL Init : %s \n", SDL_GetError());
  } else {
    printf("SDL INITIALISED\n");
    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);

    printf("Display mode is %dx%dpx @ %dhz\n", dm.w, dm.h, dm.refresh_rate);
  }
}

/**
 * Initialise an SDL Window and Renderer
 *
 * This uses SDL_CreateWindowAndRenderer. They can alternatively be created separately. See SDL2 Docs
 */
void init_window_and_renderer()
{
  if (SDL_CreateWindowAndRenderer(_width, _height, SDL_WINDOW_SHOWN, &_window, &_renderer) != 0) {
    printf("[Error] Creating Window and Renderer: %s\n", SDL_GetError());
    exit(0);
  } else {
    printf("Created Window and Renderer %dx%d\n", _width, _height);
  }
}

/**
 * Initialise TTF
 */
void init_ttf()
{
  TTF_Init();
}

/**
 * Initialise mixer
 */
void init_audio()
{
  if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != 0) {
    printf("[Error] Error Initialising Audio : %s\n", SDL_GetError());
  } else {
    printf("Audio Initialised\n");
  }
}

/**
 * Setup a sample header text
 */
void setup_header_text()
{
  // See CMakeLists.txt to see how the resources folder is copied from the root to the bin folder
  _font = TTF_OpenFont("resources/OpenSans-Regular.ttf", 18);

  SDL_Surface *textSurface = TTF_RenderText_Blended(_font, "Mouse Click and Drag Rect. Press [Escape] to Exit",
                                                    white);
  _headerText = SDL_CreateTextureFromSurface(_renderer, textSurface);

  _headerTextRect.x = _width / 2 - textSurface->w / 2;
  _headerTextRect.y = 0;
  _headerTextRect.w = textSurface->w;
  _headerTextRect.h = textSurface->h;

  SDL_FreeSurface(textSurface);

  // The value will probably be misreported as never used in CLion, however I think it should always be set
  textSurface = NULL;
}

/**
 * Setup a sample texture
 */
void setup_texture()
{
  _image = NULL;

  // Load image at specified path
  SDL_Surface *loadedSurface = IMG_Load("resources/floor.png");
  if (loadedSurface == NULL) {
    printf("[Error] Unable to load image : %s\n", SDL_GetError());
    exit(0);
  } else {
    _image = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
    if (_image == NULL) {
      printf("[Error] Unable to create texture : %s\n", SDL_GetError());
    }

    SDL_FreeSurface(loadedSurface);
  }
}

/**
 * Setup a window app icon
 */
void setup_window_icon()
{
  SDL_Surface *iconSurface = NULL;
  iconSurface = IMG_Load("resources/pong_icon.png");

  // The icon requires the window pointer NOT the renderer
  SDL_SetWindowIcon(_window, iconSurface);

  // ...and can now free the appicon surface
  SDL_FreeSurface(iconSurface);
}

/**
 * Play a sample audio file
 */
void play_audio()
{
  _music = Mix_LoadMUS("resources/sound.ogg");
  if (Mix_PlayMusic(_music, -1) != 0) {
    printf("[Error] Could not play music : %s", Mix_GetError());
  }
}

/**
 * Handles dragging the sample rectangle around. Demonstrates mouse motion events.
 * @param e
 */
void handle_mouse_drag(SDL_Event e)
{
  if (e.type == SDL_MOUSEBUTTONDOWN) {
    // Point where mouse button down occurs
    SDL_Point p = {.x = e.motion.x, .y = e.motion.y};

    if (SDL_PointInRect(&p, &_sampleRect)) {
      _inSampleRect = SDL_TRUE;
    }
  }

  if (e.type == SDL_MOUSEBUTTONUP && _inSampleRect == SDL_TRUE) {
    _inSampleRect = SDL_FALSE;
  }

  if (e.type == SDL_MOUSEMOTION && _inSampleRect == SDL_TRUE) {
    _sampleRect.x += e.motion.xrel;
    _sampleRect.y += e.motion.yrel;
  }
}

/**
 * The main game loop. Continues to loop until Escape or an SDL_Quit event occurs
 */
void main_loop()
{
  SDL_bool loop = SDL_TRUE;
  SDL_Event event;

  while (loop) {

    // Allow quiting with escape key by polling for pending events
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        loop = SDL_FALSE;
      } else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:
            loop = SDL_FALSE;
            break;
          default:
            loop = SDL_TRUE;
        }
      }
      handle_mouse_drag(event);
    }

    // Blank out the renderer with all black
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
    SDL_RenderClear(_renderer);

    // Note that all rendercopys are order specific.

    // Render the sample texture. We could use a source and/or destination rect to render to
    // but for now we'll just use it as a background
    SDL_RenderCopy(_renderer, _image, NULL, NULL);

    // Render the sample rectangle
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 1);
    SDL_RenderFillRect(_renderer, &_sampleRect);

    // Render sample text
    SDL_RenderCopy(_renderer, _headerText, NULL, &_headerTextRect);

    // Present to renderer
    SDL_RenderPresent(_renderer);
    SDL_Delay(10);
  }
}

/**
 * Main entry point
 * @return exit code
 */


////==============================================

//void Game::events() {
//  while (SDL_PollEvent(&m_ev)) {
//    switch (m_ev.type) {
//      case SDL_QUIT:m_run = false;
//        break;
//
//      case SDL_KEYDOWN:
//        if (m_ev.key.keysym.sym == SDLK_ESCAPE) {
//          m_run = false;
//        }
//        if (m_ev.key.keysym.sym == SDLK_UP || m_ev.key.keysym.sym == SDLK_DOWN ||
//            m_ev.key.keysym.sym == SDLK_RIGHT || m_ev.key.keysym.sym == SDLK_LEFT) {
//          m_player_left->set_move(m_ev.key.keysym.sym);
//        }
//        if (m_number_pl == 2) {
//          if (m_ev.key.keysym.sym == SDLK_w || m_ev.key.keysym.sym == SDLK_s ||
//              m_ev.key.keysym.sym == SDLK_d || m_ev.key.keysym.sym == SDLK_a) {
//            m_player_right->set_move(m_ev.key.keysym.sym);
//          }
//        }
//        break;
//
//      case SDL_KEYUP:
//        if (m_ev.key.keysym.sym == SDLK_UP || m_ev.key.keysym.sym == SDLK_DOWN ||
//            m_ev.key.keysym.sym == SDLK_RIGHT || m_ev.key.keysym.sym == SDLK_LEFT) {
//          m_player_left->disable_move(m_ev.key.keysym.sym);
//        }
//        if (m_number_pl == 2) {
//          if (m_ev.key.keysym.sym == SDLK_w || m_ev.key.keysym.sym == SDLK_s ||
//              m_ev.key.keysym.sym == SDLK_d || m_ev.key.keysym.sym == SDLK_a) {
//            m_player_right->disable_move(m_ev.key.keysym.sym);
//          }
//        }
//        break;
//    }
//  }
//}

/*
 *
  m_text_surface[0] = TTF_RenderText_Solid(m_window.getShrift(), "Player 1", m_text_color);

  if (m_number_pl == 2) {
    m_player2 = std::shared_ptr<Player>(new Player(POSITION::LEFT));
    m_text_surface[1] = TTF_RenderText_Solid(m_window.getShrift(), "Player 2", m_text_color);

  } else {
//    m_player2 = std::shared_ptr<Player>(new Player(POSITION::UP));
    m_text_surface[1] = TTF_RenderText_Solid(m_window.getShrift(), "Bot", m_text_color);
  }

  m_text_texture[0] = SDL_CreateTextureFromSurface(m_window.getRender(), m_text_surface[0]);
  m_text_texture[1] = SDL_CreateTextureFromSurface(m_window.getRender(), m_text_surface[1]);
 */

//  play_mus = check_goal();
//  if (play_mus) {
// play music
//    Mix_PlayMusic(m_window.m_goal, 0);
//  }

//  SDL_Rect rect;
//  rect.x = 0;
//  rect.y = 0;
//  rect.w = 15;
//  rect.h = 50;
//  m_window.draw_surface(m_color);

//  SDL_SetRenderDrawColor(m_window.getRender(), 255, 255, 255, 1);
//  SDL_RenderFillRect(m_window.getRender(), &rect);
//  m_player1->draw_surface(m_color);
//  m_player1->moving();

/*
m_player2->draw_surface(m_color);
if (NUM_PLAYERS == 2)
{
  player2->moving();
}
else
{
  player2->set_move(puck.center.x);
  player2->disable_move(puck.center.y);
  player2->moving();
}

m_ball.draw_surface(m_color);
m_ball.moving(m_window.bum);

colision(player);
colision(player2);


SDL_UpdateTexture(window.texture, NULL, m_color, WIDTH << 2);
SDL_RenderCopy(window.render, window.texture, NULL, NULL);
draw_score();
SDL_RenderPresent(window.render);

if (play_mus) {
  while (Mix_PlayingMusic());
}

*/


void Game::colision(std::shared_ptr<Player> player) {

/*
  double in = (.y+(l_paddle.h/2))-(ball.y+(ball.h/2));
  double nor = in/(l_paddle.h/2);
  double b = nor * (5*PI/12);
  velX=BALL_SPEED*cos(b);
  velY=BALL_SPEED*-sin(b);

  */

  double Dx = m_ball->center.x - player->center.x;
  double Dy = m_ball->get_center().y - player->get_center().y;
  double d = sqrt(Dx * Dx + Dy * Dy);

  if (d == 0)
    d = 0.01;

  if (d <= m_ball->get_radius() + player->get_radius()) {
    double cos_a = Dx / d;
    double sin_a = Dy / d;
    double Vn1 = player->get_speed().x * cos_a + player->get_speed().y * sin_a;
    double Vn2 = m_ball->get_speed().x * cos_a + m_ball->get_speed().y * sin_a;

    // проверка на наложение
    double dt = (m_ball->get_radius() + player->get_radius() - d) / (Vn1 - Vn2);
    if (dt > 0.6)
      dt = 0.6;
    else if (dt < -0.6)
      dt = -0.6;

    //временный сдвиг
    player->pos.x -= player->speed.x * dt;
    player->pos.y -= player->speed.y * dt;
    player->set_center();


    m_ball->pos.x -= m_ball->speed.x * dt;
    m_ball->pos.y -= m_ball->speed.y * dt;
//    m_ball.set_center();

    //перерасчет
    Dx = m_ball->center.x - player->center.x;
    Dy = m_ball->center.y - player->center.y;
    d = sqrt(Dx * Dx + Dy * Dy);

    if (d == 0)
      d = 0.01;

    cos_a = Dx / d;
    sin_a = Dy / d;

    Vn1 = player->speed.x * cos_a + player->speed.y * sin_a;
    Vn2 = m_ball->speed.x * cos_a + m_ball->speed.y * sin_a;

    double Vt2 = -m_ball->speed.x * sin_a + m_ball->speed.y * cos_a;

    //проверка направления ускорения
    if (Vn2 < 0)
      Vn2 = Vn1 - Vn2;
    else
      Vn2 += Vn1;

    m_ball->speed.x = Vn2 * cos_a - Vt2 * sin_a;
    m_ball->speed.y = Vn2 * sin_a + Vt2 * cos_a;

    //обратный сдвиг
    player->pos.x += player->speed.x * dt;
    player->pos.y += player->speed.y * dt;
    player->set_center();

    if (m_ball->speed.x > 50)
      m_ball->speed.x = 50;
    if (m_ball->speed.x < -50)
      m_ball->speed.x = -50;
    if (m_ball->speed.y > 50)
      m_ball->speed.y = 50;
    if (m_ball->speed.y < -50)
      m_ball->speed.y = -50;

    m_ball->pos.x += m_ball->speed.x * dt;
    m_ball->pos.y += m_ball->speed.y * dt;
    m_ball->set_center();

//    if (!Mix_PlayingMusic())
//      Mix_PlayMusic(window.bum, 0);

  }

}
operatortemplate <typename T>
class GameObjects{

 protected:

  Vec2i _velocity;
  int _speed;

  int _curX;
  int _curY;
  SDL_Texture* _texture;  // TODO need to destroy textures // SDL_DestroyTexture(t);
  T _boundingBox;

 public:
  // Constructors
  GameObjects() = default;
  GameObjects(GameObjects& other) = delete;
  GameObjects& operator=(GameObjects& other) = delete;
  GameObjects(GameObjects&& other) = delete;
  GameObjects& operator=(GameObjects&& other) = delete;

  // Destructor
  ~GameObjects() { SDL_DestroyTexture(_texture); }

  // Accessors
  Vec2i velocity() { return _velocity; }
  int curX() { return _curX; }
  int curY() { return _curY; }
  T boundingBox() { return _boundingBox;  }
  SDL_Texture* getTexture() { return _texture;  }

  // Modifiers
  void setTexture(SDL_Texture* t) { _texture = t; }
  void setVelocity(Vec2i v) { _velocity = v;  }
  void setSpeed(int s) { _speed = s;  }
  void curX(int n);
  void curY(int n);

  // Special functions
  virtual void render(SDL_Renderer* renderer) = 0;
  void move();
  void updateBoundingBox();
};