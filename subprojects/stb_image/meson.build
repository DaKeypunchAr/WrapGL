project('stb_image', 'c', default_options: ['cpp_std=20'])

stb_lib = library(
  'stb_image',
  'src/stbi_image.c',
  include_directories: include_directories('include'),
  link_args: ['-lm'],
  install: false,
)

stb_image_dep = declare_dependency(include_directories: include_directories('include'), link_with: stb_lib)

meson.override_dependency('stb_image', stb_image_dep)
