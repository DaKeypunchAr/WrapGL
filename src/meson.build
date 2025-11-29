sources = [
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
stb_image_dep = dependency('stb_image')

wrapgl_lib = library(
  'wrapgl',
  sources,
  include_directories: include_directories('../include'),
  dependencies: [glfw_dep, glad_dep, glm_dep, stb_image_dep],
)
wrapgl_dep = declare_dependency(
  link_with: wrapgl_lib,
  include_directories: include_directories('../include'),
  dependencies: [glfw_dep, glad_dep, glm_dep, stb_image_dep],
)

meson.override_dependency('wrapgl', wrapgl_dep)
