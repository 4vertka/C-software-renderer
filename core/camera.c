#include <camera.h>

#include <renderer.h>
#include <stdlib.h>
#include  <stdio.h>


#define MAX_CAMERAS 10

//static camera_t cameras[MAX_CAMERAS];
//static int camera_count = 0;

camera_t* camera_create(float fov,                
                        float aspect,             
                        float near,               
                        float far,                
                        vec3f_t pos,  
                        vec3f_t eye,
                        vec3f_t target,
                        vec3f_t up) {

  camera_t* cam = malloc(sizeof(*cam));//&cameras[camera_count];
  
  cam->fov = fov;
  cam->aspect = aspect;
  cam->near = near;
  cam->far = far;
  cam->position = pos;
  
  cam->eye = eye;
  cam->target = target;
  cam->up = up;

  //cam->direction = vec3_unit(vec3_minus_vec3(pos, target));
  //cam->right = vec3_unit(vec3_cross(up, cam->direction)); 
  //cam->up = vec3_cross(cam->direction, cam->right);

  cam->projection_mat = build_projection_mat(cam->fov, cam->aspect, cam->near, cam->far); 

  cam->view_mat = mat4_lookat(pos, vec3_add_vec3(pos, target), up); 
  //cam->view_mat = build_view_mat(cam->position);

  //camera_count++;

  return cam;
}  

void camera_update(camera_t* camera, input_t* in, float dt) {
  const float speed = 3.0f * dt;
  
  vec3f_t forward = vec3_unit(camera->target);
  camera->right = vec3_unit(vec3_cross(forward, camera->up));

  if (in->forward)  camera->position = vec3_add_vec3(camera->position, vec3_mul_scalar(camera->target, speed));
  if (in->backward) camera->position = vec3_add_vec3(camera->position, vec3_mul_scalar(camera->target, -speed));
  if (in->right)    camera->position = vec3_add_vec3(camera->position, vec3_mul_scalar(camera->right, speed));                  
  if (in->left)     camera->position = vec3_add_vec3(camera->position, vec3_mul_scalar(camera->right, -speed));     
  if (in->up)       camera->position = vec3_add_vec3(camera->position, vec3_mul_scalar(camera->up, speed));  
  if (in->down)     camera->position = vec3_add_vec3(camera->position, vec3_mul_scalar(camera->up, -speed));  

  camera->view_mat = mat4_lookat(camera->position, vec3_add_vec3(camera->position, forward), camera->up);
}

void camera_free(camera_t* camera) {
  free(camera);
}
