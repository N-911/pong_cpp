#ifndef PONG_SRC_WINDOW_H_
#define PONG_SRC_WINDOW_H_

#include <map>
#include "Settings.h"
#include "IObserver.h"
#include "EventManager.h"

class Window : public IObserver {

public:
    Window(EventManager& observable);

    virtual ~Window();

    void update_status(SDL_Event& event) override;

    TTF_Font* get_shrift() const { return m_shrift; }
    SDL_Renderer* get_render() const { return m_renderer; }

    SDL_Texture* get_texture(std::string key);
    SDL_Texture* load_texture(const char* file);

private:
    SDL_Window* m_window;
    TTF_Font* m_shrift;
    SDL_Renderer* m_renderer;
    std::map<std::string, SDL_Texture*> m_textures;

    SDL_Color m_text_color;
    EventManager& m_observer;
    int m_current_id;

//  Mix_Music	*m_bum;
//  Mix_Music	*m_goal;

    void init_SDL();
    void create_window();
    void init_window_and_renderer();
    void setup_window_icon();
};

#endif //PONG_SRC_WINDOW_H_
