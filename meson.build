project(
    'cpp_skeleton', 
    'cpp',
    version: '1.0'
)

cpp_skeleton_include_dir = include_directories('include')
cpp_skeleton_src_main = [
    'src/main.cpp',
]


format_dep = dependency('fmt')

executable(
    'cpp_skeleton',
    include_directories: cpp_skeleton_include_dir,
    sources: [cpp_skeleton_src_main, ],
    dependencies: [format_dep, ],
    install: true,
)