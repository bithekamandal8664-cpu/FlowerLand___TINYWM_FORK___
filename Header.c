#include <unistd.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include "Flower.h"

void flower_launch(const char *program) {
  if (fork() == 0) {
       execlp(program, program, NULL);
       _exit(1);
  }
}
void flower_wallpaper(const char *wallpaper) {
  if (fork() == 0) {
      execlp("feh", "feh", "--bg-fill", wallpaper, NULL);
      _exit(1);
  }
}
void flower_exit(Display *dpy) {
  XCloseDisplay(dpy);
  exit(0);
}
