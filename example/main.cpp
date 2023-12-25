#include "osfeng.h"

using namespace osfeng;

class Game : public App {
public:
  Game(int refresh_rate) : App(refresh_rate) {} 
private:
  void on_update_start() override {
    window->draw_line(0, 0, 1280, 720);
  }
};

int main (int argc, char *argv[]) {
  Game game(60);

  game.run();

  return 0;
}
