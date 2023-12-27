#include "window.h"
#include <SDL_events.h>
#include <SDL_mouse.h>
#include <SDL_video.h>
#include <stdexcept>

using namespace std;

namespace osfeng::window {
  Window::Window (const char *p_title, int p_width, int p_height, WINDOWTYPE p_type)
    : _width(p_width),    width(_width),
      _height(p_height),  height(_height),
      _title(p_title),    title(_title),
      isCloseRequested(_isCloseRequested) {

    _init_sdl_modules();

    _create_window();

    set_type(p_type);

    _create_gl_context();

    _init_glew();
  }

  Window::~Window() {
    // Unload all textures
    for (auto [name, spr] : _sprites) { delete spr; }
    _sprites.clear();

    // Unload all fonts
    for (auto [name, fnt] : _fonts) { TTF_CloseFont(fnt); }
    _fonts.clear();

    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
  }

  // - methods -
  // ~ main
  auto Window::update_events() -> void {
    input._update();

    if (lockCursor) { set_cursor_position(_width / 2, _height / 2); }

    SDL_Event e;
    while(SDL_PollEvent(&e))
      if (e.type == SDL_QUIT) { _isCloseRequested = true; }
  }

  auto Window::update_surface() -> void {
    gl_test();
  }

  // ~ window
  auto Window::set_title(const char *title) -> void {
    SDL_SetWindowTitle(_window, "title");
  }
  
  auto Window::set_size(int width, int height) -> void {
    SDL_SetWindowSize(_window, width, height);
    _width = width;
    _height = height;
  }

  auto Window::set_type(WINDOWTYPE type) -> void {
    switch (type) {
      case WINDOWTYPE::WINDOWED:
        SDL_SetWindowFullscreen(_window, SDL_WINDOW_SHOWN);
        break;
      case WINDOWTYPE::FULLSCREEN:
        SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN);
    }
  }

  auto Window::set_cursor_position(int x, int y) -> void {
    SDL_WarpMouseInWindow(_window, x, y);
  }

  auto Window::get_ticks() -> Uint32 {
    return SDL_GetTicks();
  }

  // ~ resources
  auto Window::load_sprite(const char *path, const char *name) -> void {
    // Check if sprite with such name alredy loaded
    if (_sprites.contains(name))
      throw runtime_error("Sprite with name \"" + string(name) + "\" already exists");

    SDL_Texture *texture = IMG_LoadTexture(_renderer, path);

    // Check if texture was successfuly loaded
    if (not texture)
      throw runtime_error( SDL_GetError() );

    _sprites[name] = new Sprite(texture);
  }

  auto Window::load_font(const char *path, int size, const char *name) -> void {
    // Check if sprite with such name alredy loaded
    if (_fonts.contains(name))
      throw runtime_error("Fonst with name \"" + string(name) + "\" already exists");

    TTF_Font *font = TTF_OpenFont(path, size);

    // Check if font was successfuly loaded
    if (not font)
      throw runtime_error( SDL_GetError() );

    _fonts[name] = font;
  }

  // ~ draw
  auto Window::gl_test() -> void {
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(0.0f, 0.0f);
    glEnd();

    SDL_GL_SwapWindow(_window);
  }

  auto Window::set_clear_color(float r, float g, float b) -> void {
    glClearColor(r, g, b, 1.0f);
  }

  // internal methods
  // ~ init
  auto Window::_init_sdl_modules()  -> void {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
      throw runtime_error(SDL_GetError());

    if (TTF_Init() < 0)
      throw runtime_error(TTF_GetError());

    if (IMG_Init(IMG_INIT_PNG) < 0)
      throw runtime_error(IMG_GetError());
  }

  auto Window::_init_glew() -> void {
    if (glewInit() != GLEW_OK)
      throw runtime_error("Could not initialize glew.");

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
  }

  auto Window::_create_window() -> void {
    _window = SDL_CreateWindow(
      _title, 
      SDL_WINDOWPOS_CENTERED, 
      SDL_WINDOWPOS_CENTERED, 
      _width, _height, 
      SDL_WINDOW_SHOWN
    );

    if (_window == NULL)
      throw runtime_error(SDL_GetError());
  }

  auto Window::_create_gl_context() -> void {
    _glContext = SDL_GL_CreateContext(_window);

    if (_glContext == NULL)
      throw runtime_error(SDL_GetError());
  }

  auto Window::_create_renderer()   -> void {
    _renderer = SDL_CreateRenderer(
      _window, -1, SDL_RENDERER_ACCELERATED
    );

    if (_renderer == NULL)
      throw runtime_error(SDL_GetError());
  }

  // ~ draw
  auto Window::_render_text(const char *text, SDL_Rect *rect) -> SDL_Texture* {
    SDL_Surface *textsurf = TTF_RenderText_Solid(_fonts[_curfont], text, _drawColor);

    // Check if surface successfuly created
    if (not textsurf)
      throw runtime_error( TTF_GetError() );

    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, textsurf);

    // Check if texture successfuly created
    if (not texture)
      throw runtime_error( SDL_GetError() );
    
    rect->w = textsurf->w;
    rect->h = textsurf->h;

    SDL_FreeSurface(textsurf);

    return texture;
  }
}
