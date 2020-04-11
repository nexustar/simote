server_sources = [
  'main.c',
  'network.c',
  'rtp.c',
  'frame.c',
  'decode.c',
  'render.c',
  'input.c'
  ]

server_deps = [
  dependency('sdl2'),
  dependency('libavcodec'),
  dependency('libavformat'),
  dependency('libavutil')
  ]

executable('simote-client', server_sources, dependencies: server_deps, install: true)
