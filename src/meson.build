sources = [
  'core.cpp',
  'texture.cpp',
  'window.cpp',
  'glfw.cpp',
  'vertex_array.cpp',
  'vertex_buffer.cpp',
  'shader_program.cpp',
  'renderer.cpp',
]

glfw_dep = dependency('glfw3', fallback: ['glfw', 'glfw_dep'])
glad_dep = dependency('glad')
glm_dep = dependency('glm')

wrapgl = library(
  'wrapgl',
  sources,
  include_directories: include_directories('../include'),
  dependencies: [glfw_dep, glad_dep, glm_dep],
)
wrapgl_dep = declare_dependency(
  link_with: wrapgl,
  include_directories: include_directories('../include'),
)

meson.override_dependency('wrapgl', wrapgl_dep)
