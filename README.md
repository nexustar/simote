# simote
A tool to streaming desktop

## build

dependencies: sdl2, ffmpeg, libevdev

```
$ meson build
$ ninja -C build
```

## run

on client

```
$  ./build/client/simote-client -s xx.xx.xx.xx -p 8848 -l 9005 -w 1280 -h 720
```
-w and -h means the weidth and weight of window

on server(as root)
```
# ./build/server/simote-server -S 1920:1080 -s 1280:720 -a 1920:1080:0:0
```

- -S means the resolution of display

- -s means scale video to another resolution

- -a means information about ABS mouse input, if you only have one display, use display resolution and two "0", if you have more than one display, use the whole resolution and the start coordinate of streaming display

- -c means crtc_id ,which is used to choose display, you could list all crtc_id by `modetest -e`, or leave blank to choose default one

