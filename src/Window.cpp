#include "Window.h"
#include "Settings.h"
#include "iostream"

using std::cout;
using std::endl;

Window::Window(EventManager& observable)
        :m_observer(observable)
{
    cout << "Window Construtor" << endl;
    init_SDL();
    init_window_and_renderer();
    setup_window_icon();

    // register Observer
    m_observer.attach(this);
    cout << "Attach Window to observer id =" << ++m_observer_id << endl;
    this->m_current_id = m_observer_id;

    m_textures["background"] = load_texture("resources/floor.png");
    m_textures["ball"] = load_texture("resources/red_ball.dms");

    m_text_color.r = 255;
    m_text_color.g = 255;
    m_text_color.b = 0;
    m_text_color.a = 255;
}

Window::~Window()
{
    cout << "Window destructor" << endl;
    TTF_CloseFont(m_shrift);
    TTF_Quit();

//  Mix_FreeMusic(m_bum);
//  Mix_FreeMusic(m_goal);
    Mix_CloseAudio();

    for (auto key : m_textures)
        SDL_DestroyTexture(key.second);

    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

SDL_Texture* Window::load_texture(const char* file)
{

    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(file);
    if (loadedSurface == NULL) {
        std::cout << "Unable to load image " << file << ". SDL_image error: " << IMG_GetError() << "\n";
    }
    else {
        newTexture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
        if (newTexture == NULL) {
            std::cout << "Unable to create texture from " << file << ". SDL Error: " << SDL_GetError() << "\n";
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

void Window::init_SDL()
{
    // Initialise SDL2 and output some useful display info
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout << "[Error] SDL Init : " << SDL_GetError() << endl;
        exit(1);
    }
    else {
        cout << "SDL INITIALISED\n";
        SDL_DisplayMode dm;
        SDL_GetCurrentDisplayMode(0, &dm);
        cout << "Display mode is " << dm.w << "x" << dm.h << "px @ " << dm.refresh_rate << "hz\n";
    }

    // Initialise TTF
    if (TTF_Init() == -1) {
        cout << TTF_GetError() << endl;
        exit(1);
    }
    m_shrift = TTF_OpenFont("resources/OpenSans-Regular.ttf", 40);
    if (!m_shrift) {
        cout << TTF_GetError() << endl;
        exit(1);
    }

    // Initialise mixer
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != 0) {
        cout << "[Error] Error Initialising Audio : " << Mix_GetError() << endl;
        exit(1);
    }
    else {
        cout << "Audio Initialised\n";
    }
//  m_bum = Mix_LoadMUS("resources/bum.wav");
//  m_goal = Mix_LoadMUS("resources/goal.wav");
}

void Window::create_window()
{
    if (!(m_window = SDL_CreateWindow("PONG", SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_SHOWN |
                    SDL_WINDOW_OPENGL))) {
        cout << SDL_GetError() << endl;
        exit(1);
    }
    else {
        cout << "Created Window and Renderer " << W << "x" << H << endl;
    }
    if (!(m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED))) {
        cout << SDL_GetError() << endl;
        exit(1);
    }



//    if (!(m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ARGB8888,
//            SDL_TEXTUREACCESS_STREAMING, W, H))) {
//        cout << SDL_GetError() << endl;
//        exit(1);
//    }
}

void Window::init_window_and_renderer()
{
    if (SDL_CreateWindowAndRenderer(W, H, SDL_WINDOW_SHOWN, &m_window, &m_renderer) != 0) {
        printf("[Error] Creating Window and Renderer: %s\n", SDL_GetError());
        exit(0);
    }
    else {
        printf("Created Window and Renderer %dx%d\n", W, H);
    }
}

void Window::setup_window_icon()
{
    SDL_Surface* iconSurface = NULL;
    iconSurface = IMG_Load("resources/pong_icon.png");

    // The icon requires the window pointer NOT the renderer
    SDL_SetWindowIcon(m_window, iconSurface);

    // ...and can now free the appicon surface
    SDL_FreeSurface(iconSurface);
}

void Window::update_status(SDL_Event& event)
{
}

SDL_Texture* Window::get_texture(std::string key)
{
    if (m_textures.count(key)) {
        return m_textures[key];
    }
    return nullptr;
}
