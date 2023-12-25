#include "osfeng.h"

using namespace osfeng::window;

int main (int argc, char *argv[]) {
  Window *window = new Window();

  while (not window->isCloseRequested) {
    window->update_events();
    window->draw_line(0, 0, 1280, 720);
    window->update_surface();
  }

  delete window;

  return 0;
}
