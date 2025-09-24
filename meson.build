project(
  'fingerprint-connect',
  'cpp',
  default_options: [
    'cpp_std=c++17',
    # '-stdlib=libc++',
  ],
)

# libcxx_flags = [
#   '-nostdinc++',
#   '-I/usr/include/c++/v1',
#   '-isystem', '/usr/include',
#   '-isystem', '/usr/include/x86_64-linux-gnu',
# ]
# add_project_arguments(libcxx_flags, language: 'cpp')
# add_project_link_arguments(['-lc++', '-lc++abi'], language: 'cpp')
subdir('src')
subdir('tests')
