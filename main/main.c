#include <stdlib.h>

#include <math/vector.h>
#include <math/matrix.h>
#include <renderer.h>
#include <line.h>
#include <stdio.h>

#include <mesh.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <system/system.h>


vec3f_t p0 = {100, 100,0};            
vec3f_t p1 = {100, 500, 0};           
vec3f_t p2 = {500, 500, 0};           

uint32_t color_to_uint(int r, int g, int b)
{
	return (uint32_t)((r << 16) + (g << 8) + (b << 0));
}

void draw(framebuffer_t* fb) {
  plot_triangle(fb, p0, p1, p2, color_to_uint(255, 255, 255));  
}

int main()
{
  system_t sys;
  system_init(&sys, "main window", 800, 600);
  
  input_t in = {
    .quit = false
  };

  framebuffer_t fb = system_get_framebuffer(&sys);

  while (!in.quit) {
    system_poll(&sys, &in);

    draw(&fb);

    system_present(&sys);
  }
  
  system_shutdown(&sys);
}

  /*
  vec3f_t vertices[3] = {
    {-0.5f, -0.5f, 0.0f},
    {0.5f, -0.5f, 0.0f},
    {0.0f, 0.5f, 0.0f}
  };

  uint16_t indices[3] = {
    0, 1, 2
  };

  int vert_count = 3;
  int indices_count = 3;

  
  
  
  
  mat4x4_t model = build_model_mat(-55.0f, (vec3f_t){1.0f, 0.0f, 0.0f});
  mat4x4_t view = build_view_mat((vec3f_t){0.0f, 0.0f, -3.0f});
  mat4x4_t proj = build_projection_mat(45.0f, (float)width/height, 1.0f, 100.0f);
  
  mat4x4_t mvp = build_mvp_mat(proj, view, model);

  vec3f_t screen[3];

  while (!quit) {
    loop();
  }

  //mfb_update_state state;
  //do {
    //memset(buffer, 0, width * height * 4);
  
    for (int i = 0; i < indices_count; i++) {
      vec4f_t clip = build_mvp_position(mvp, vertices[indices[i]]);

      float inv_w = 1/clip.w;
      float x_w = clip.x * inv_w;
      float y_w = clip.y * inv_w;
      float z_w = clip.z * inv_w;

      screen[i].x = (x_w + 1.0f) * 0.5 * fb.window_width;
      screen[i].y = (1.0f - y_w) * 0.5 * fb.window_height;
      screen[i].z = 0.0 + z_w * (1.0 - 0.0);
    }


  SDL_Quit();
    //plot_triangle(&fb, screen[0], screen[1], screen[2], );

  return 0;
}
*/
