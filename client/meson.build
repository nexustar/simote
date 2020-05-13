client_sources = [
  'main.c',
  'network.c',
  'rtp.c',
  'frame.c',
  'decode.c',
  'render.c',
  'input.c'
  ]

client_deps = [
  dependency('sdl2'),
  dependency('libavcodec'),
  dependency('libavformat'),
  dependency('libavutil')
  ]

executable('simote-client', client_sources, dependencies: client_deps, install: true)
