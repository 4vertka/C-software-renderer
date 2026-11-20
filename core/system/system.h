#ifndef SYSTEM_H 
#define SYSTEM_H 

#include <stdbool.h>
#include  <SDL3/SDL.h>

typedef struct {
  SDL_Window* window;
  SDL_Surface* surface;
  SDL_Renderer* renderer;
  int width;
  int height;
} system_t;

typedef struct {
  bool quit;
} input_t;

bool system_init(system_t* sys, const char* title, int w, int h);
void system_poll(system_t* sys, input_t* in);
void system_present(system_t* sys);
void system_shutdown(system_t* sys);

#endif 
