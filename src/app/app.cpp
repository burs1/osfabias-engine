#include "app.h"

using namespace osfeng::window;

namespace osfeng {
  App::App(int refresh_rate)
  : window(_window), delta_time(_delta_time) {
    _window = new Window();

    set_refresh_rate(refresh_rate);

    on_create();
  }

  auto App::set_refresh_rate(int refresh_rate) -> void {
    _update_delay = 1000 / refresh_rate;
  }

  auto App::run() -> void {
    while (not _window->isCloseRequested) {
      if (not _is_update_time()) { continue; }
      
      on_update_start();

      _window->update_events();
      _window->update_surface();

      on_update_end();
    }

    _clean_up();
  }

  auto App::_is_update_time() -> bool {
    Uint32 current_time = window->get_ticks();
    if (current_time < _next_update_time) { return false; }

    _delta_time = (current_time - _last_update_time) / 1000.0;
    _last_update_time = current_time;
    _next_update_time = (window->get_ticks() / _update_delay + 1) * _update_delay;
    return true;
  }

  auto App::_clean_up() -> void {
    on_clean_up();
    delete _window;
  }
}
