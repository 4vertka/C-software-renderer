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

vec3f_t p0 = {100, 100,0};            
vec3f_t p1 = {100, 500, 0};           
vec3f_t p2 = {500, 500, 0};           

uint32_t color_to_uint(int r, int g, int b)
{
	return (uint32_t)((r << 16) + (g << 8) + (b << 0));
}

int main()
{
  system_t sys;
  system_init(&sys, "main window", 800, 600);
  
  input_t in = {
    .quit = false
  };

  framebuffer_t fb = system_get_framebuffer(&sys);

  vec3f_t vertices[3] = {
    {-0.5f, -0.5f, 0.0f},                    
    {0.5f, -0.5f, 0.0f},                     
    {0.0f, 0.5f, 0.0f}                       
  };

  uint16_t indices[3] = {       
    0, 1, 2                     
  };                            

  //mesh_t* mesh = mesh_init(vertices, 3, indices, 3);

  mat4x4_t model = build_model_mat(0.0f, (vec3f_t){1.0f, 0.0f, 0.0f});             
  
  camera_t* cam = camera_create(45.0f, (float)fb.width/fb.height, 0.1f, 100.f, (vec3f_t){0.0f, 0.0f, -3.0f}, (vec3f_t){0,0,0});
  //mat4x4_t view = build_view_mat((vec3f_t){0.0f, 0.0f, -3.0f});                     
  //mat4x4_t proj = build_projection_mat(45.0f, (float)fb.width/fb.height, 1.0f, 100.0f);   
    
  mesh_t* mesh = mesh_create(vertices, 3, indices, 3);
  transform_t transform = transform_create((vec3f_t){0,0,0}, (vec3f_t){1,0,0}, (vec3f_t){1,1,1});
  object_t* object = object_create(mesh, transform, color_to_uint(255, 255, 255));

  //mat4x4_t mvp = build_mvp_mat(cam->projection_mat, cam->view_mat, model);                                  

  while (!in.quit) {
    memset(fb.buffer, 0, sizeof(*fb.buffer));
    system_poll(&sys, &in);

    object_draw(object, &fb, cam->view_mat);
    //mesh_draw(&fb, mesh, mvp, color_to_uint(255, 255, 255));

    system_present(&sys);
  }
  
  system_shutdown(&sys);
}
