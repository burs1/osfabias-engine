#include "osfeng.h"
#include <iostream>

using namespace osfeng;

class Game : public App {
public:
  Game(int refresh_rate) : App(refresh_rate) {} 
private:
  void on_update_start() override {
    window->draw_line(0, 0, 1280, 720);
    window->lockCursor = true;
    window->set_cursor_visibility(false);
    window->set_type(WINDOWTYPE::FULLSCREEN);
  }

  void on_update_end() override {
    if (window->input.get_key_pressed("w"))
      std::cout << "w pressed\n";
    if (window->input.get_key_released("w"))
      std::cout << "w released\n";

    if (window->input.get_mouse_pressed(1))
      std::cout << "lmb pressed\n";
    if (window->input.get_mouse_released(1))
      std::cout << "lmb released\n";

    int dx, dy;
    window->input.get_mouse_delta(dx, dy);
    std::cout << dx << ' ' << dy << '\n';
  }
};

int main (int argc, char *argv[]) {
  Game game(60);

  game.run();

  return 0;
}
