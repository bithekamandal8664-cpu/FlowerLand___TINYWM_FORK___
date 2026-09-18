/* TinyWM is written by Nick Welch <nick@incise.org> in 2005 & 2011.
 * and this is modified by Aronno <bithekamandal8664@gmail.com> in August 2026
 * This software is in the public domain
 * this software is now renamed as "FlowerLand"
 * and is provided AS IS, with NO WARRANTY. */

#include <X11/Xlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

char terminal[64] = "xterm";
char bar[64] = "polybar";
char wallpaper[256] = "";
void tile(Display *dpy, int screen, Window windows[], int window_count)
{
    int width = DisplayWidth(dpy, screen);
    int height = DisplayHeight(dpy, screen);

    for (int i = 0; i < window_count; i++) {
        if (i == 0)
            XMoveResizeWindow(dpy, windows[i], 0, 0,
                              width / 2, height);
        else
            XMoveResizeWindow(dpy, windows[i],
                              width / 2,
                              (i - 1) * height / (window_count - 1),
                              width / 2,
                              height / (window_count - 1));
    }

    XFlush(dpy);
}
void load_config(void)
{
        char path[256];
    char *home = getenv("HOME");

    if (!home) return;

    snprintf(path, sizeof(path),
             "%s/.config/FlowerLand/config", home);

    FILE *fp = fopen(path, "r");
    if (!fp) return;

    char line[256];

    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "terminal=", 9) == 0)
            sscanf(line + 9, "%63s", terminal);

        else if (strncmp(line, "bar=", 4) == 0)
            sscanf(line + 4, "%63s", bar);

        else if(strncmp(line, "wallpaper=", 10) == 0)
            sscanf(line + 10, "%255s", wallpaper);
    }

    fclose(fp);
}

int main(void)
{
    Display * dpy;
    int screen;
    Window windows[32];
    int window_count = 0;
    XWindowAttributes attr;
    XButtonEvent start;
    XEvent ev;

        load_config();

    if(!(dpy = XOpenDisplay(0x0))) return 1;
        XGrabKey(dpy, XKeysymToKeycode(dpy, XStringToKeysym("Return")), Mod4Mask,
            DefaultRootWindow(dpy), True, GrabModeAsync, GrabModeAsync);
    XGrabKey(dpy, XKeysymToKeycode(dpy, XStringToKeysym("F1")), Mod1Mask,
            DefaultRootWindow(dpy), True, GrabModeAsync, GrabModeAsync);
    XGrabButton(dpy, 1, Mod1Mask, DefaultRootWindow(dpy), True,
            ButtonPressMask|ButtonReleaseMask|PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None);
    XGrabButton(dpy, 3, Mod1Mask, DefaultRootWindow(dpy), True,
            ButtonPressMask|ButtonReleaseMask|PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None);

        if (fork() == 0) {
    execlp(bar, bar, NULL);
    _exit(1);
    }
       if (fork() == 0) {
           execlp("feh", "feh", "--bg-fill", wallpaper, NULL);
           _exit(1);
    }
    start.subwindow = None;
    for(;;)
    {
        XNextEvent(dpy, &ev);
 if (ev.type == MapRequest) {
    Window win = ev.xmaprequest.window;

    if (window_count < 32) {
        windows[window_count++] = win;
        XMapWindow(dpy, win);
        tile(dpy, screen, windows, window_count);
    }
        }
        if(ev.type == KeyPress && ev.xkey.keycode == XKeysymToKeycode(dpy, XStringToKeysym("Return"))) {
                if (fork() == 0) {
                        execlp(terminal, terminal, NULL);
                        _exit(1);
                }
        }
        if(ev.type == KeyPress && ev.xkey.subwindow != None)
            XRaiseWindow(dpy, ev.xkey.subwindow);
        else if(ev.type == ButtonPress && ev.xbutton.subwindow != None)
        {
            XGetWindowAttributes(dpy, ev.xbutton.subwindow, &attr);
            start = ev.xbutton;
        }
        else if(ev.type == MotionNotify && start.subwindow != None)
        {
            int xdiff = ev.xbutton.x_root - start.x_root;
            int ydiff = ev.xbutton.y_root - start.y_root;
            XMoveResizeWindow(dpy, start.subwindow,
                attr.x + (start.button==1 ? xdiff : 0),
                attr.y + (start.button==1 ? ydiff : 0),
                MAX(1, attr.width + (start.button==3 ? xdiff : 0)),
                MAX(1, attr.height + (start.button==3 ? ydiff : 0)));
        }
        else if(ev.type == ButtonRelease)
            start.subwindow = None;
    }
}
