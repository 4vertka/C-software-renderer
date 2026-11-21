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

  camera_t* cam = camera_create(45.0f, (float)fb.width/fb.height, 0.1f, 100.f, (vec3f_t){0.0f, 0.0f, -3.0f}, (vec3f_t){0,0,0});
    
  mesh_t* mesh = mesh_create(vertices, 3, indices, 3);
  transform_t transform = transform_create((vec3f_t){0,0,0}, (vec3f_t){1,0,0}, (vec3f_t){1,1,1});
  object_t* object = object_create(mesh, transform, color_to_uint(255, 255, 255), RENDER_FILLED);

 // mat4x4_t mvp = build_mvp_mat(cam->projection_mat, cam->view_mat, model);                                  

  while (!in.quit) {
    memset(fb.buffer, 0, fb.width * fb.height * sizeof(*fb.buffer));
    system_poll(&sys, &in);

    //object->transform.rotation.z += 0.1f;
    object_draw(object, &fb, cam->view_mat);

    system_present(&sys);
  }
  
  mesh_free(mesh);
  object_free(object);
  system_shutdown(&sys);
}
