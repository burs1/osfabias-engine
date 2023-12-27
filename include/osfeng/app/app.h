#pragma once

#include <iostream>
#include "../window/window.h"

namespace osfeng {
  class App {
  public:
    App(int);

    // - methods -
    // ~ main
    auto run() -> void;

    auto set_refresh_rate(int) -> void;

    window::Window* const &window;
    const double &delta_time;

  private:
    // - internal methods -
    // ~ main
    auto _is_update_time() -> bool;

    auto _clean_up()       -> void;

    // ~ events
    virtual auto on_init()         -> void {}

    virtual auto on_update_start() -> void {}
    
    virtual auto on_update_end()   -> void {}

    virtual auto on_clean_up()     -> void {}

    // - vars -
    window::Window *_window;

    double _delta_time = 0.0;

    Uint32 _update_delay = 0;
    Uint32 _next_update_time = 0;
    Uint32 _last_update_time = 0;
  };
}
