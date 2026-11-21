#include "system.h"

bool system_init(system_t* sys, const char* title, int w, int h) {
  SDL_Init(SDL_INIT_VIDEO);

  sys->window = SDL_CreateWindow(title, w, h, 0);
  if (!sys->window) return false;

  sys->surface = SDL_GetWindowSurface(sys->window);
  if (!sys->surface) return false;

  sys->renderer = SDL_CreateSoftwareRenderer(sys->surface);
  if (!sys->surface) return false;

  sys->width = w;
  sys->height = h;

  return true;
} 

void system_poll(system_t* sys, input_t* in) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
      case SDL_EVENT_QUIT: in->quit = true; break;
      
      case SDL_EVENT_KEY_DOWN: { 
        switch (e.key.key) {
          case SDLK_ESCAPE: in->quit = true; break;
          case SDLK_W: in->forward = true; break;
          case SDLK_S: in->backward = true; break;
        }
      }
      case SDL_EVENT_KEY_UP: {
        switch (e.key.key) {
          case SDLK_W: in->forward = false; break;
          case SDLK_S: in->backward = false; break;
        }
      }
    }
    /*
    if (e.type == SDL_EVENT_QUIT)
      in->quit = true;
    if ((e.type == SDL_EVENT_KEY_DOWN) && (e.key.key == SDLK_ESCAPE)) {
      in->quit = true;
    }
    if ((e.type == SDL_EVENT_KEY_DOWN) && (e.key.key == SDLK_W)) {
      
    }
    */
  }
} 

void system_present(system_t* sys) {
  SDL_UpdateWindowSurface(sys->window);
} 

void system_shutdown(system_t* sys) {
  SDL_DestroyRenderer(sys->renderer);
  SDL_DestroySurface(sys->surface);
  SDL_DestroyWindow(sys->window);
  SDL_Quit();
}

framebuffer_t system_get_framebuffer(system_t* sys) {
  return (framebuffer_t) {
    .buffer = sys->surface->pixels,
    .width = sys->surface->w,
    .height = sys->surface->h
  };
}
