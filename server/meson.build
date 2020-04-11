server_sources = [
  'main.c',
  'network.c',
  'input.c'
  ]

server_deps = [
  dependency('sdl2'),
  dependency('libevdev')
  ]

executable('simote-server', server_sources, dependencies: server_deps, install: true)
