#include <camera.h>

#include <renderer.h>
#include <stdlib.h>
#include  <stdio.h>

static vec3f_t up = {0, 1, 0};

camera_t* camera_create(float fov, float aspect, float z_near, float z_far, vec3f_t position, vec3f_t target) {
  camera_t* cam = malloc(sizeof(*cam));

  cam->fov = fov;
  cam->aspect = aspect;
  cam->z_near = z_near;
  cam->z_far = z_far;
  cam->position = position;
  cam->target = target;

  vec3f_t direction = vec3_unit(vec3_minus_vec3(target, position));
  cam->pitch = asinf(direction.y);
  cam->yaw = atan2f(direction.z, direction.x);

  cam->projection_mat = mat4_perspective(cam->fov, cam->aspect, cam->z_near, cam->z_far);
  cam->view_mat = mat4_lookat(position, target, up);

  return cam;
}

void camera_update(camera_t* camera, input_t* in, float dt) {
  const float speed = 3.0f * dt;
  
  vec3f_t forward = {
    cos(camera->pitch) * cosf(camera->yaw),
    sinf(camera->pitch),
    cosf(camera->pitch) * sinf(camera->yaw)
  };
  
  forward = vec3_unit(forward);

  vec3f_t right = vec3_unit(vec3_cross(forward, up));

  if (in->forward)  camera->position = vec3_add_vec3(camera->position, vec3_mul_scalar(forward, speed));
  if (in->backward) camera->position = vec3_add_vec3(camera->position, vec3_mul_scalar(forward, -speed));
  if (in->right)    camera->position = vec3_add_vec3(camera->position, vec3_mul_scalar(right, speed));                  
  if (in->left)     camera->position = vec3_add_vec3(camera->position, vec3_mul_scalar(right, -speed));     
  if (in->up)       camera->position = vec3_add_vec3(camera->position, vec3_mul_scalar(up, speed));  
  if (in->down)     camera->position = vec3_add_vec3(camera->position, vec3_mul_scalar(up, -speed));  

  camera->target = vec3_add_vec3(camera->position, forward);

  camera->view_mat = mat4_lookat(camera->position, camera->target, up);
}


void camera_free(camera_t* camera) {
  free(camera);
}
