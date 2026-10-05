# FlowerLand___TINYWM_FORK___

This window manager is basically a fork of TinyWM and renamed to FlowerLand :3
just copy the file and compile? (i think?)
and ywah, add config file so you can edit easiky like this
```bash
bar="your bar"
terminal="your terminal"
wallpaper="your wallpaper"
```
here's how to run
```bash
wget https://raw.githubusercontent.com/bithekamandal8664-cpu/FlowerLand___TINYWM_FORK___/refs/heads/main/Flower.h
wget https://raw.githubusercontent.com/bithekamandal8664-cpu/FlowerLand___TINYWM_FORK___/refs/heads/main/Header.c
https://raw.githubusercontent.com/bithekamandal8664-cpu/FlowerLand___TINYWM_FORK___/refs/heads/main/FlowerLand.c
mkdir ~/.config/FlowerLand/
touch ~/.configFlowerLandd/config
gcc FlowerLand.c Header.c -o FlowerLand -lX11
./FlowerLand
```
and if you are in X11 session, try to leave and test it in TTY, 
## WARNING
this window manager runs Xserver (x11) which is old to today's standard, but you can use it of you want:3
