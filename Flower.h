#ifndef FLOWER_H
#define FLOWER_H

#include <X11/Xlib.h>

void flower_launch(const char *program);
void flower_wallpaper(const char *wallpaper);
void flower_exit(Display *dpy);

#endif
