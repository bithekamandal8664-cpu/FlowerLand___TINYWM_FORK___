#include <unistd.h>
#include "Flower.h"

void flower_launch(const *char program) {
  if (fork == 0) {
       execlp(program, program, NULL);
       _exit(1);
  }
}
void flower_wallpaper(const *char wallpaper) {
  if (fork == 0) {
      execlp("feh", "feh", wallpaper, NULL);
      _exit(1);
  }
}
