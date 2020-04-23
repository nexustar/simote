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

on server(as root)
```
# ./build/server/simote-server -c 0 -w 1280 -h 1080
```

-c means crtc_id ,which is used to choose display, you could list all crtc_id by `modetest -e`, or leave blank to choose default one

