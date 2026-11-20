#include <stdlib.h>

#include <MiniFB.h>

#include <math/vector.h>
#include <math/matrix.h>

static const int width = 800;
static const int height = 600;

int main()
{
  struct mfb_window* window = mfb_open_ex("window", width, height, MFB_WF_RESIZABLE);
  if (!window) {
    return EXIT_FAILURE;
  }

  uint32_t* buffer = malloc(width * height * 4);

  mfb_update_state state;
  do {
    
    state = mfb_update_ex(window, buffer, width, height);
    if (state != MFB_STATE_OK)
      break;

  } while (mfb_wait_sync(window));

  free(buffer);
  buffer = NULL;
  window = NULL;

  return 0;
}
