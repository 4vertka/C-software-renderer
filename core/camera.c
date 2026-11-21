#include <camera.h>

#include <renderer.h>

#define MAX_CAMERAS 10

static camera_t cameras[MAX_CAMERAS];
static int camera_count = 0;

camera_t* camera_create(float fov,                
                        float aspect,             
                        float near,               
                        float far,                
                        vec3f_t pos,              
                        vec3f_t target) {

  camera_t* cam = &cameras[camera_count];
  
  cam->fov = fov;
  cam->aspect = aspect;
  cam->near = near;
  cam->far = far;
  cam->position = pos;
  cam->target = target;

  cam->projection_mat = build_projection_mat(cam->fov, cam->aspect, cam->near, cam->far); 

  cam->view_mat = build_view_mat(cam->position);

  camera_count++;

  return cam;
}     
