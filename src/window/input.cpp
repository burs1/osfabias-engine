#include "input.h"
#include <SDL_mouse.h>

namespace osfeng::window {
  InputManager::InputManager() {
    _inputs = SDL_GetKeyboardState(NULL);
    _mouseState = SDL_GetMouseState(&_mouseX, &_mouseY);
  }

  // - methods -
  auto InputManager::bind(const char *key, const char *bindName) -> void {
    _keyBinds[bindName] = SDL_GetScancodeFromName(key);
  }
  
  auto InputManager::get_bind_down(const char *bindName) -> bool {
    return _inputs[ _keyBinds[bindName] ];
  }

  auto InputManager::get_bind_pressed(const char *bindName) -> bool {
    return _inputs[ _keyBinds[bindName] ] and not _prevInputs[ _keyBinds[bindName] ];
  }

  auto InputManager::get_bind_released(const char *bindName) -> bool {
    return _prevInputs[ _keyBinds[bindName] ] and not _inputs[ _keyBinds[bindName] ];
  }
  
  auto InputManager::get_key_down(const char *keyName) -> bool {    
    SDL_Scancode scancode = SDL_GetScancodeFromName(keyName);
    return _inputs[ scancode ];
  }

  auto InputManager::get_key_pressed(const char *keyName) -> bool {
    SDL_Scancode scancode = SDL_GetScancodeFromName(keyName);
    return _inputs[ scancode ] and not _prevInputs[ scancode ];
  }
  
  auto InputManager::get_key_released(const char *keyName) -> bool {
    SDL_Scancode scancode = SDL_GetScancodeFromName(keyName);
    return _prevInputs[ scancode ] and not _inputs[ scancode ];
  }

  auto InputManager::get_mouse_pos(int &x, int &y) -> void {
    x = _mouseX; y = _mouseY;
  }
  
  auto InputManager::get_mouse_delta(int &x, int &y) -> void {
    x = _mouseX - _prevMouseX; y = _mouseY - _prevMouseY;
  }

  auto InputManager::get_mouse_down(int button) -> bool {
    return SDL_BUTTON(button) & _mouseState;
  }
    
  auto InputManager::get_mouse_pressed(int button) -> bool {
    return (SDL_BUTTON(button) & _mouseState) and not (SDL_BUTTON(button) & _prevMouseState);
  }
  
  auto InputManager::get_mouse_released(int button) -> bool {
    return (SDL_BUTTON(button) & _prevMouseState) and not (SDL_BUTTON(button) & _mouseState);
  }


  // - internal methods -
  auto InputManager::_update() -> void {
    for (int i = 0; i < 255; ++i) { _prevInputs[i] = _inputs[i]; }
    _prevMouseState = _mouseState;
    _prevMouseX = _mouseX; _prevMouseY = _mouseY;
    _mouseState = SDL_GetMouseState(&_mouseX, &_mouseY);
  }
}
