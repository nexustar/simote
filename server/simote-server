#!/usr/bin/sh
ffmpeg -device /dev/dri/card0 -f kmsgrab -framerate 60 -i - -vf 'hwmap=derive_device=vaapi,crop=1920:1080:0:0,scale_vaapi=w=1920:h=1080:format=nv12' -c:v h264_vaapi -qp 24 -bf 0 -f rtp rtp://127.0.0.1:9005
