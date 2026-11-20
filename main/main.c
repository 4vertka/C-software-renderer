#include <stdlib.h>

#include <MiniFB.h>

#include <math/vector.h>
#include <math/matrix.h>
#include <renderer.h>
#include <line.h>
#include <stdio.h>

static const int width = 800;
static const int height = 600;

int main()
{
  struct mfb_window* window = mfb_open_ex("window", width, height, MFB_WF_RESIZABLE);
  if (!window) {
    return EXIT_FAILURE;
  }

  uint32_t* buffer = malloc(width * height * 4);

  framebuffer_t fb = {
    .buffer=buffer,
    .width = width,
    .height = height
  };
  
  vec3f_t vertices[3] = {
    {-0.5f, -0.5f, 0.0f},
    {0.5f, -0.5f, 0.0f},
    {0.0f, 0.5f, 0.0f}
  };

  int vert_count = 3;

  vec3f_t p0 = {100, 100,0};
  vec3f_t p1 = {100, 500, 0};
  vec3f_t p2 = {500, 500, 0};
  
  mat4x4_t model = build_model_mat(-55.0f, (vec3f_t){1.0f, 0.0f, 0.0f});
  mat4x4_t view = build_view_mat((vec3f_t){0.0f, 0.0f, -3.0f});
  mat4x4_t proj = build_projection_mat(45.0f, (float)width/height, 1.0f, 100.0f);
  
  mat4x4_t mvp = build_mvp_mat(proj, view, model);

  vec3f_t screen[3];

  mfb_update_state state;
  do {
    memset(buffer, 0, width * height * 4);
  
    for (int i = 0; i < vert_count; i++) {
      vec4f_t clip = build_mvp_position(mvp, vertices[i]);

      float inv_w = 1/clip.w;
      float x_w = clip.x * inv_w;
      float y_w = clip.y * inv_w;
      float z_w = clip.z * inv_w;

      screen[i].x = (x_w + 1.0f) * 0.5 * fb.width;
      screen[i].y = (1.0f - y_w) * 0.5 * fb.height;
      screen[i].z = 0.0 + z_w * (1.0 - 0.0);

      printf("clip: %f %f %f %f\n", clip.x, clip.y, clip.z, clip.w);
printf("screen: %f %f %f\n", screen[i].x, screen[i].y, screen[i].z);
    }

    plot_triangle(&fb, screen[0], screen[1], screen[2], MFB_RGB(255, 255, 255));
    //plot_triangle(&fb, p0, p1, p2, MFB_RGB(255, 255, 255));

    state = mfb_update_ex(window, buffer, width, height);
    if (state != MFB_STATE_OK)
      break;

  } while (mfb_wait_sync(window));

  free(buffer);
  buffer = NULL;
  window = NULL;

  return 0;
}
