project(
    'jam-web-crawler', 
    'cpp',
    version: '1.0',
    default_options: ['cpp_std=c++17', 'werror=true']
)

jam_web_crawler_include_dir = include_directories('include')

jam_web_crawler_src = [
    'src/PageDownloader.cpp',
    'src/CrawlerConfig.cpp',
    'src/Page.cpp',
]

jam_web_crawler_src_main = [
    'src/main.cpp',
]

jam_web_crawler_src_main_proto = [
    'src/prototype.cpp',
]


format_dep = dependency('fmt')
curl_dep = dependency('libcurl')
gumbo_dep = dependency('gumbo')
sqlitecpp_dep = dependency('sqlitecpp')

cmake = import('cmake')
googletest_sub = cmake.subproject('googletest')
gtestmain_dep = googletest_sub.dependency('gtest_main')
gtest_dep = googletest_sub.dependency('gtest')
toml_dep = dependency('tomlplusplus')


executable(
    'jam-web-crawler-prototype',
    include_directories: jam_web_crawler_include_dir,
    sources: [jam_web_crawler_src_main_proto, ],
    dependencies: [
        curl_dep, 
        format_dep, 
        gumbo_dep, 
        sqlitecpp_dep, 
    ],
    cpp_args: ['-Wall', '-Wextra', '-Wpedantic', '-Og'],
    install: true,
)

jam_crawler_deps = [
    curl_dep, 
    format_dep, 
    gumbo_dep, 
    sqlitecpp_dep, 
    toml_dep, 
]

jam_crawler_lib = library(
    'jam-web-crawler-lib',
    include_directories: jam_web_crawler_include_dir,
    sources: jam_web_crawler_src,
    dependencies: [jam_crawler_deps, ],
)

jam_crawler_dep = declare_dependency(
    include_directories: jam_web_crawler_include_dir,
    link_with: jam_crawler_lib,
    dependencies: [jam_crawler_deps, ],
)

executable(
    'jam-web-crawler',
    include_directories: jam_web_crawler_include_dir,
    sources: [jam_web_crawler_src_main, ],
    dependencies: [
        jam_crawler_dep, 
    ],
    cpp_args: ['-Wall', '-Wextra', '-Wpedantic', '-Og'],
    install: true,
)

subdir('tests')