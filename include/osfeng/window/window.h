#pragma once

#include <map>
#include <sdl.h>
#include <string>
#include "input.h"
#include "sprite.h"
#include <stdexcept>
#include <sdl_ttf.h>
#include <GL/glew.h>
#include <sdl_image.h>

namespace osfeng {
  enum class WINDOWTYPE {
    WINDOWED,
    FULLSCREEN
  };
}

namespace osfeng::window {
  class Window {
  public:
    explicit Window (const char* p_title="window", int p_width=1280, int p_height=720, WINDOWTYPE p_type=WINDOWTYPE::WINDOWED);

    ~Window();

    // - methods - 
    // ~ main
    auto update_events()                            -> void;

    auto update_surface()                           -> void;

    // ~ window
    auto set_title(const char*)                     -> void;

    auto set_size(int, int)                         -> void;

    auto set_type(WINDOWTYPE)                       -> void;

    auto set_cursor_position(int, int)              -> void;

    auto get_ticks()                                -> Uint32;

    // ~ resources
    auto load_sprite(const char*, const char*)          -> void;

    auto load_font(const char*, int size, const char*)  -> void;

    // ~ draw
    auto gl_test() -> void;
    
    auto set_clear_color(float, float, float)                                   -> void;

    // - vars -
    // ~ read only
    const bool &isCloseRequested;
    const int &width, &height;
    const char* &title;

    bool lockCursor = true;

    // ~ components
    InputManager input;

  private:
    // - internal methods -
    // ~ init
    auto _init_sdl_modules()  -> void;

    auto _init_glew()         -> void;

    auto _create_window()     -> void;

    auto _create_gl_context() -> void;

    auto _create_renderer()   -> void;

    // ~ rendering
    auto _render_text(const char*, SDL_Rect*) -> SDL_Texture*;

    // - vars -
    // ~ window info
    int _width, _height;
    const char *_title;

    // ~ sdl, opengl & window
    SDL_Window *_window;
    SDL_Renderer *_renderer;

    SDL_GLContext _glContext;

    bool _fullscreen;
    bool _isCloseRequested = false;

    // ~ drawing
    SDL_Color _clearColor = SDL_Color{0, 0, 0, 255};
    SDL_Color _drawColor = SDL_Color{255, 255, 255, 255};

    const char *_curfont = "";

    // ~ resources
    std::map< const char*, window::Sprite* > _sprites;
    std::map< const char*, TTF_Font* > _fonts;

  };
}
