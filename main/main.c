#include <stdlib.h>

#include <math/vector.h>
#include <math/matrix.h>
#include <renderer.h>
#include <stdio.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <system/system.h>
#include <camera.h>

#include <scene/mesh.h>
#include <scene/object.h>
#include <scene/transform.h>
#include <scene/scene.h>

#include <elip.h>

#define TARGET_FRAME_MS       16

uint32_t color_to_uint(int r, int g, int b)
{
	return (uint32_t)((r << 16) + (g << 8) + (b << 0));
}

int main()
{
  system_t sys;
  system_init(&sys, "main window", 800, 600);
  
  input_t in = {
    .quit = false,
    .forward = false,
    .backward = false,
    .right = false,
    .left = false,
    .up = false,
    .down = false
  };

  framebuffer_t fb = system_get_framebuffer(&sys);

  camera_t* cam = camera_create(radins(45.0f), (float)fb.width/fb.height, 0.1f, 100.0f, (vec3f_t){0,0,-3}, (vec3f_t){0,0,0});

  elip_t* elip = elip_create((vec3f_t){1.0f,1.0f,1.0f}, 36, 18, (vec3f_t){0,0,0}, (vec3f_t){1,0,0}, (vec3f_t){1,1,1}, color_to_uint(255, 255, 255), RENDER_WIREFRAME);

  dt_t delta_time = {                 
    .last = SDL_GetTicks(),           
    .now = 0,                         
    .dt = 0                           
  };                                  

  while (!in.quit) {
    delta_time.now = SDL_GetTicks();
    delta_time.dt = (delta_time.now - delta_time.last) / 1000.0f; 
    delta_time.last = delta_time.now;

    memset(fb.buffer, 0, fb.width * fb.height * sizeof(*fb.buffer));
    system_poll(&sys, &in);
    camera_update(cam, &in, delta_time.dt);

    elip_draw(elip, &fb, cam->view_mat, cam->projection_mat);

    system_present(&sys);

    Uint64 frame_ms = SDL_GetTicks() - delta_time.now;
    if (frame_ms < TARGET_FRAME_MS) 
      SDL_Delay(TARGET_FRAME_MS - frame_ms);
  }
  
  elip_free(elip);
  camera_free(cam);
  system_shutdown(&sys);
}
