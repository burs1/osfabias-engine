#pragma once

#include <map>
#include <sdl.h>
#include <string>
#include "input.h"
#include "sprite.h"
#include <stdexcept>
#include <sdl_ttf.h>
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

    auto set_cursor_visibility(bool)                -> void;

    auto set_cursor_position(int, int)              -> void;

    auto get_ticks()                                -> Uint32;

    // ~ resources
    auto load_sprite(const char*, const char*)          -> void;

    auto load_font(const char*, int size, const char*)  -> void;

    // ~ draw
    auto set_clear_color(Uint8, Uint8, Uint8)                                   -> void;

    auto set_draw_color(Uint8, Uint8, Uint8, Uint8)                             -> void;

    auto draw_line(int, int, int, int)                                          -> void;

    auto draw_triangle(int, int, int, int, int, int, bool fill=true)            -> void;

    auto draw_rect(int, int, int, int, bool fill=true)                          -> void;
    
    auto set_font(const char*)                                                  -> void;

    auto draw_text(const char*, int, int)                                       -> void;

    auto draw_text_ex(const char*, int, int, float, float, float)               -> void;
     
    auto draw_sprite(const char*, int, int)                                     -> void;
    
    auto draw_sprite_ex(const char*, int, int, float, float, float, int, int)   -> void;

    // - vars -
    // ~ read only
    const bool &isCloseRequested;
    const int &w, &h;

    bool lockCursor = true;

    // ~ components
    InputManager input;

  private:
    // - internal methods -
    // ~ rendering
    auto _render_text(const char*, SDL_Rect*) -> SDL_Texture*;

    // - vars -
    // ~ info
    int _width, _height;

    // ~ sdl & window
    SDL_Window *_window;
    SDL_Renderer *_renderer;

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
