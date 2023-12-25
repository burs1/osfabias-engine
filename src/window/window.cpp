#include "window.h"
#include <SDL_keyboard.h>
#include <SDL_mouse.h>
#include <SDL_render.h>
#include <SDL_video.h>

using namespace std;

namespace osfeng::window {
  // ~ constructors and destructors
  Window::Window (const char *p_title, int p_width, int p_height, WINDOWTYPE p_type)
    : isCloseRequested(_isCloseRequested), w(_width), h(_height) {
    _width = p_width;
    _height = p_height;

    // Init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
      throw runtime_error(SDL_GetError());

    // Init TTF
    if (TTF_Init() < 0)
      throw runtime_error(TTF_GetError());

    // Init IMG
    if (IMG_Init(IMG_INIT_PNG) < 0)
      throw runtime_error(IMG_GetError());

    // Create window
    _window = SDL_CreateWindow(
      p_title, 
      SDL_WINDOWPOS_CENTERED, 
      SDL_WINDOWPOS_CENTERED, 
      _width, _height, 
      SDL_WINDOW_SHOWN
    );

    if (_window == NULL)
      throw runtime_error(SDL_GetError());

    set_type(p_type);
    
    // Create renderer
    _renderer = SDL_CreateRenderer(
      _window, -1, SDL_RENDERER_ACCELERATED
    );

    if (_renderer == NULL)
      throw runtime_error(SDL_GetError());
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
    SDL_RenderPresent(_renderer);

    // Clear renderer
    auto [cr, cg, cb, ca] = _clearColor;
    SDL_SetRenderDrawColor(_renderer, cr, cg, cb, ca);
    SDL_RenderClear(_renderer);

    // Set draw color back
    auto [dr, dg, db, da] = _drawColor;
    SDL_SetRenderDrawColor(_renderer, dr, dg, db, da);
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

  auto Window::set_cursor_visibility(bool flag) -> void {
    SDL_ShowCursor(flag ? SDL_ENABLE : SDL_DISABLE);
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
  auto Window::set_clear_color(Uint8 r, Uint8 g, Uint8 b) -> void {
    _clearColor = SDL_Color{r, g, b, 255};
  }
  
  auto Window::set_draw_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) -> void {
    SDL_SetRenderDrawColor(_renderer, r, g, b, a);
    _drawColor = SDL_Color{r, g, b, a};
  }
  
  auto Window::draw_line(int x1, int y1, int x2, int y2) -> void {
    SDL_RenderDrawLine(_renderer, x1, y1, x2, y2);
  }

  auto Window::draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, bool fill) -> void {
    if (not fill) {
      draw_line(x1, y1, x2, y2);
      draw_line(x2, y2, x3, y3);
      draw_line(x3, y3, x1, y1);
      return;
    }

    SDL_Vertex verts[] = {
      {{(float)x1, (float)y1}, _drawColor},
      {{(float)x2, (float)y2}, _drawColor},
      {{(float)x3, (float)y3}, _drawColor}
    };
    SDL_RenderGeometry(_renderer, NULL, verts, 3, NULL, 0);
  }

  auto Window::draw_rect(int x1, int y1, int x2, int y2, bool fill) -> void {
    if (not fill) {
      draw_line(x1, y1, x2, y1);
      draw_line(x2, y1, x2, y2);
      draw_line(x2, y2, x1, y2);
      draw_line(x1, y2, x1, y1);
      return;
    }

    SDL_Rect draw_rect{x1, y1, x2-x1, y2-y1};
    SDL_RenderDrawRect(_renderer, &draw_rect);
  }

  auto Window::set_font(const char* fontname) -> void {
    _curfont = fontname;
  }

  auto Window::draw_text(const char* text, int x, int y) -> void {
    SDL_Rect txtr_rect{0, 0};
    SDL_Texture *texture = _render_text(text, &txtr_rect);

    SDL_Rect draw_rect{
      x, y,
      txtr_rect.w,
      txtr_rect.h
    };

    if (SDL_RenderCopy(_renderer, texture, &txtr_rect, &draw_rect) < 0)
      throw runtime_error(SDL_GetError());

    SDL_DestroyTexture(texture);
  }
 
  auto Window::draw_text_ex(const char* text, int x, int y, float xscale, float yscale, float angle) -> void {
    SDL_Rect txtr_rect{0, 0};
    SDL_Point center{0, 0};
    SDL_Texture *texture = _render_text(text, &txtr_rect);

    SDL_Rect draw_rect{
      x, y,
      int(txtr_rect.w * xscale),
      int(txtr_rect.h * yscale)
    };

    if (SDL_RenderCopyEx(_renderer, texture, &txtr_rect, &draw_rect, angle, &center, SDL_FLIP_NONE) < 0)
      throw runtime_error(SDL_GetError());
    SDL_DestroyTexture(texture);
  }
 
  auto Window::draw_sprite(const char* sprname, int x, int y) -> void {
    Sprite *spr = _sprites[sprname];
    SDL_Rect draw_rect{x, y, spr->w, spr->h};

    if (SDL_RenderCopy(_renderer, spr->texture, &spr->rect, &draw_rect) < 0)
      throw runtime_error( SDL_GetError() );
  }

  auto Window::draw_sprite_ex(const char* sprname, int x, int y, float xscale, float yscale, float angle, int xcent, int ycent) -> void {
    Sprite *spr = _sprites[sprname];
    SDL_Rect draw_rect{x, y, int(spr->w * xscale), int(spr->h * yscale)};
    SDL_Point center{xcent, ycent};

    if (SDL_RenderCopyEx(_renderer, spr->texture, &spr->rect, &draw_rect, angle, &center, SDL_FLIP_NONE) < 0)
      throw runtime_error( SDL_GetError() );
  }

  // internal methods
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
