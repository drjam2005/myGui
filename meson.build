project(
  'gui',
  'cpp',
  version : '0.1',
  meson_version : '>= 1.3.0',
  default_options : ['warning_level=3', 'cpp_std=c++20'],
)

raylibDep = declare_dependency(
  include_directories: include_directories('include'),
  link_args: ['-L' + meson.project_source_root() / 'lib', '-lraylib'],
)

dependencies = [
  raylibDep,
]

src = [
  'src/gui.cpp',
  'src/main.cpp',
]
exe = executable(
  'gui',
  src,
  install : true,
  dependencies : dependencies,
)

test('basic', exe)
