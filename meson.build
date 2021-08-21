project('csvreader', 'cpp',
        default_options: [
          #'warning_level=3',
          #'buildtype=release',
          'buildtype=debug',
        ])
# ↑名前付きの引数を渡すときは、名前も書く必要があります。
# どういう引数が渡せるかは https://mesonbuild.com/Reference-manual.html#project を見ましょう。
# ちなみに、default_optionsとして渡せるオプションは、ビルドディレクトリの中でmeson configureで一覧が見えます。


includes = include_directories('include')
csvreader_dep = declare_depencency(include_directories: includes)

executable(
    'foo', ['src/test.cpp'],
    include_directories: includes)
