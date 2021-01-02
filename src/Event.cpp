#include "Event.h"

void Event::OnEvent(SDL_Event* event) {

  switch (event->type) {
    case SDL_QUIT:m_loop = SDL_FALSE;
      break;
    case SDL_KEYDOWN:
      if (event->key.keysym.sym == SDLK_ESCAPE) {
        m_loop = SDL_FALSE;
        break;
      }
      if (event->key.keysym.sym == SDLK_SPACE) {
//        m_pause = !m_pause;
//  onPause();
        break;
      }

      if (event->key.keysym.sym == SDLK_p) {  // new ball for testing
//        m_ball->set_new_ball(1);
//        m_ball->moving();
      }
      if (event->key.keysym.sym == SDLK_UP || event->key.keysym.sym == SDLK_DOWN ||
          event->key.keysym.sym == SDLK_RIGHT || event->key.keysym.sym == SDLK_LEFT) {
//        m_player_left->set_move(event->key.keysym.sym);

      }
//      if (m_number_pl == 2) {
      if (event->key.keysym.sym == SDLK_w || event->key.keysym.sym == SDLK_s ||
          event->key.keysym.sym == SDLK_d || event->key.keysym.sym == SDLK_a) {
//          m_current_player_right->set_move(event.key.keysym.sym);
      }
//      }
      break;
    case SDL_KEYUP:
      if (event->key.keysym.sym == SDLK_UP || event->key.keysym.sym == SDLK_DOWN ||
          event->key.keysym.sym == SDLK_RIGHT || event->key.keysym.sym == SDLK_LEFT) {
//        m_player_left->disable_move(event.key.keysym.sym);
      }
//      if (m_number_pl == 2) {
      if (event->key.keysym.sym == SDLK_w || event->key.keysym.sym == SDLK_s ||
          event->key.keysym.sym == SDLK_d || event->key.keysym.sym == SDLK_a) {
//          m_current_player_right->disable_move(event.key.keysym.sym);
      }
//      }
      break;
    default:m_loop = SDL_TRUE;
  }
}
    /*
}
  switch(Event->type) {
    case SDL_WINDOWEVENT: {
      switch(Event->window.event) {
//        case SDL_APPMOUSEFOCUS: {
//          if ( Event->active.gain )    OnMouseFocus();
//          else                OnMouseBlur();
//
//          break;
//        }
//        case SDL_APPINPUTFOCUS: {
//          if ( Event->active.gain )    OnInputFocus();
//          else                OnInputBlur();
//
//          break;
//        }
//        case SDL_APPACTIVE:    {
//          if ( Event->active.gain )    OnRestore();
//          else                OnMinimize();
//
//          break;
//        }
//      }
//      break;
//    }

    case SDL_KEYDOWN: {
      Event->key.keysym.sym;
//      Event->key.keysym.mod,Event->key.keysym.sym;
        break;
    }

    case SDL_KEYUP: {
      Event->key.keysym.sym;
//      Event->key.keysym.mod,Event->key.keysym.sym;
      break;
    }

    case SDL_MOUSEMOTION: {
      OnMouseMove(Event->motion.x,Event->motion.y,Event->motion.xrel,Event->motion.yrel,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
      break;
    }

    case SDL_MOUSEBUTTONDOWN: {
      switch(Event->button.button) {
        case SDL_BUTTON_LEFT: {
          OnLButtonDown(Event->button.x,Event->button.y);
          break;
        }
        case SDL_BUTTON_RIGHT: {
          OnRButtonDown(Event->button.x,Event->button.y);
          break;
        }
        case SDL_BUTTON_MIDDLE: {
          OnMButtonDown(Event->button.x,Event->button.y);
          break;
        }
      }
      break;
    }

    case SDL_MOUSEBUTTONUP:    {
      switch(Event->button.button) {
        case SDL_BUTTON_LEFT: {
          OnLButtonUp(Event->button.x,Event->button.y);
          break;
        }
        case SDL_BUTTON_RIGHT: {
          OnRButtonUp(Event->button.x,Event->button.y);
          break;
        }
        case SDL_BUTTON_MIDDLE: {
          OnMButtonUp(Event->button.x,Event->button.y);
          break;
        }
      }
      break;
    }

    case SDL_QUIT: {
      m_loop = SDL_FALSE;
    }
      OnExit();
      break;
    }

    case SDL_SYSWMEVENT: {
      //Ignore
      break;
    }

//    case SDL_WINDOWEVENT_RESIZED: {
////      event->window.windowID, event->window.data1,
////          event->window.data2);
////    }
//      Event->resize.w,Event->resize.h;
//      break;
//    }

//    case SDL_VIDEOEXPOSE: {
//      OnExpose();
//      break;
//    }

    default: {
      OnUser(Event->user.type,Event->user.code,Event->user.data1,Event->user.data2);
      break;
    }
  }
     */

/*
void Event::OnInputFocus() {
  //Pure virtual, do nothing
}

void Event::OnInputBlur() {
  //Pure virtual, do nothing
}

//void Event::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
  //Pure virtual, do nothing
//}

//void Event::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
  //Pure virtual, do nothing
//}

void Event::OnMouseFocus() {
  //Pure virtual, do nothing
}

void Event::OnMouseBlur() {
  //Pure virtual, do nothing
}

void Event::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle) {
  //Pure virtual, do nothing
}

void Event::OnMouseWheel(bool Up, bool Down) {
  //Pure virtual, do nothing
}

void Event::OnLButtonDown(int mX, int mY) {
  //Pure virtual, do nothing
}

void Event::OnLButtonUp(int mX, int mY) {
  //Pure virtual, do nothing
}

void Event::OnRButtonDown(int mX, int mY) {
  //Pure virtual, do nothing
}

void Event::OnRButtonUp(int mX, int mY) {
  //Pure virtual, do nothing
}

void Event::OnMButtonDown(int mX, int mY) {
  //Pure virtual, do nothing
}

void Event::OnMButtonUp(int mX, int mY) {
  //Pure virtual, do nothing
}

void Event::OnJoyAxis(Uint8 which,Uint8 axis,Sint16 value) {
  //Pure virtual, do nothing
}

void Event::OnJoyButtonDown(Uint8 which,Uint8 button) {
  //Pure virtual, do nothing
}

void Event::OnJoyButtonUp(Uint8 which,Uint8 button) {
  //Pure virtual, do nothing
}

void Event::OnJoyHat(Uint8 which,Uint8 hat,Uint8 value) {
  //Pure virtual, do nothing
}

void Event::OnJoyBall(Uint8 which,Uint8 ball,Sint16 xrel,Sint16 yrel) {
  //Pure virtual, do nothing
}

void Event::OnMinimize() {
  //Pure virtual, do nothing
}

void Event::OnRestore() {
  //Pure virtual, do nothing
}

void Event::OnResize(int w,int h) {
  //Pure virtual, do nothing
}

void Event::OnExpose() {
  //Pure virtual, do nothing
}

 */
