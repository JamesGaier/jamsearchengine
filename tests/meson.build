
crawler_test_srcs = [
    'CrawlerConfigTest.cpp',
    'PageTest.cpp',
]

crawler_test_exe = executable(
    'crawler_test',
    sources: crawler_test_srcs,
    dependencies: [jam_crawler_dep, gtestmain_dep, gtest_dep, ],
    cpp_args: ['-Wall', '-Wextra', '-Wpedantic', '-Og'],
)

install_data('test_config.toml', install_dir: meson.build_root() / 'tests')

test(
    'crawler_test',
    crawler_test_exe,
)