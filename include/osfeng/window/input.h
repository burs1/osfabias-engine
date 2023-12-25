#pragma once

#include <map>
#include <sdl.h>

namespace osfeng::window {
  class InputManager {
  friend class Window;
  public:
    InputManager();

    // - methods -
    auto bind(const char*, const char*)     -> void;

    auto get_bind_down(const char*)         -> bool;

    auto get_bind_pressed(const char*)      -> bool;

    auto get_bind_released(const char*)     -> bool;
    
    auto get_key_down(const char*)          -> bool;

    auto get_key_pressed(const char*)       -> bool;
    
    auto get_key_released(const char*)      -> bool;

    auto get_mouse_pos(int&, int&)          -> void;

    auto get_mouse_delta(int&, int&)        -> void;

    auto get_mouse_down(int)                -> bool;
    
    auto get_mouse_pressed(int)             -> bool;
    
    auto get_mouse_released(int)            -> bool;

    bool lockCursor = false;

  private:
    // - internal methods -
    auto _update() -> void;

    // - vars -
    std::map< const char*, SDL_Scancode > _keyBinds;
    Uint32 _mouseState, _prevMouseState;
    int _mouseX, _mouseY, _prevMouseX, _prevMouseY;

    const Uint8 *_inputs;
    Uint8 _prevInputs[285];

  };
}
