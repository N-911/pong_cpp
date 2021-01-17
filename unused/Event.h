#ifndef PONG_SRC_EVENT_H_
#define PONG_SRC_EVENT_H_

#include "../src/Settings.h"

class Event {
public:
    Event() { };

    virtual ~Event() { };

    virtual void OnEvent(SDL_Event* event);

    virtual void OnInputFocus() = 0;

    virtual void OnInputBlur() = 0;

//  virtual void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);

//  virtual void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

    virtual void OnMouseFocus() = 0;

    virtual void OnMouseBlur() = 0;

    virtual void OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle) = 0;

    virtual void OnMouseWheel(bool Up, bool Down) = 0;    //Not implemented

    virtual void OnLButtonDown(int mX, int mY) = 0;

    virtual void OnLButtonUp(int mX, int mY) = 0;

    virtual void OnRButtonDown(int mX, int mY) = 0;

    virtual void OnRButtonUp(int mX, int mY) = 0;

    virtual void OnMButtonDown(int mX, int mY) = 0;

    virtual void OnMButtonUp(int mX, int mY) = 0;

    virtual void OnMinimize() = 0;

    virtual void OnRestore() = 0;

    virtual void OnResize(int w, int h) = 0;

    virtual void OnExpose() = 0;

    virtual void OnExit() = 0;

    virtual void OnUser(Uint8 type, int code, void* data1, void* data2) = 0;

protected:
    SDL_bool m_loop;
};

#endif //PONG_SRC_EVENT_H_
