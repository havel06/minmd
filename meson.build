project('minmd', 'cpp')

md4cdep = dependency('md4c')
gtkmmdep = dependency('gtkmm-3.0')

source_files = [ 'src/config.cpp', 'src/file_handling.cpp',
'src/file_watcher.cpp', 'src/image_widget.cpp',
'src/initialize.cpp', 'src/main.cpp',
'src/main_label.cpp', 'src/inner_vbox.cpp',
'src/main_scrolled_window.cpp',
'src/main_window.cpp', 'src/parse.cpp' ]

executable('minmd', source_files, dependencies : [md4cdep, gtkmmdep], install : true , cpp_args : '-std=c++17')
