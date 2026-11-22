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

#include <time.h>

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
    .quit = false,
    .forward = false,
    .backward = false,
    .right = false,
    .left = false,
    .up = false,
    .down = false
  };

  framebuffer_t fb = system_get_framebuffer(&sys);

  vec3f_t vertices[] = {
    {-0.5, -0.5,  0.5},                    
    {0.5, -0.5,  0.5},                     
    {0.5,  0.5,  0.5},
    {-0.5,  0.5,  0.5},
    {-0.5, -0.5, -0.5},
    {0.5, -0.5, -0.5},
    {0.5,  0.5, -0.5},
    {-0.5,  0.5, -0.5}
  };

  uint16_t indices[] = {       
    0, 1, 2,  2, 3, 0,
    1, 5, 6,  6, 2, 1,
    5, 4, 7,  7, 6, 5,
    4, 0, 3,  3, 7, 4,
    3, 2, 6,  6, 7, 3,
    4, 5, 1,  1, 0, 4
  };                            

  camera_t* cam = camera_create(radins(45.0f), (float)fb.width/fb.height, 0.1f, 100.0f, (vec3f_t){0,0,-3}, (vec3f_t){0,0,0});

  //mesh_t* mesh = mesh_create(vertices, sizeof(vertices)/sizeof(vec3f_t), indices, sizeof(indices)/sizeof(uint16_t));
  //transform_t transform = transform_create((vec3f_t){0,0,0}, (vec3f_t){1,0,0}, (vec3f_t){1,1,1});
  //object_t* object = object_create(mesh, transform, color_to_uint(255, 255, 255), RENDER_WIREFRAME);

  elip_t* elip = elip_create((vec3f_t){1.0f,1.0f,1.0f}, 36, 18, (vec3f_t){0,0,0}, (vec3f_t){1,0,0}, (vec3f_t){1,1,1}, color_to_uint(255, 255, 255), RENDER_WIREFRAME);

  float angle = 0.0;
  float camera_angle = 0.0;

  Uint32 last = SDL_GetTicks();

  while (!in.quit) {
    Uint32 now = SDL_GetTicks();
    float dt = (now - last) / 1000.0f;
    last = now;

    memset(fb.buffer, 0, fb.width * fb.height * sizeof(*fb.buffer));
    system_poll(&sys, &in);
    //camera_update(cam, &in, dt);

    const float radius = 10.0f;
    camera_angle += dt * 0.5f;

    float camX = sinf(camera_angle) * radius;
    float camZ = cosf(camera_angle) * radius;

    //cam->view_mat = mat4_lookat((vec3f_t){camX, 0.0, camZ}, (vec3f_t){0,0,0}, (vec3f_t){0.0, 1.0f, 0.0});

    //angle += dt * 1.0f;
    //object->transform.rotation.y = angle;
    //object->transform.rotation.x = angle;
    
    elip_draw(elip, &fb, cam->view_mat);

    //object_draw(object, &fb, cam->view_mat);

    system_present(&sys);
  }
  
  camera_free(cam);
  //mesh_free(mesh);
  //object_free(object);
  system_shutdown(&sys);
}
