cmake_minimum_required(VERSION 3.13.4)
project(minmd)
set(CMAKE_CXX_STANDARD 17)
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(pkgs REQUIRED gtkmm-3.0 md4c)

file(GLOB SOURCES "src/*.cpp")

add_executable(minmd ${SOURCES})

target_link_libraries(minmd ${pkgs_LIBRARIES})
target_include_directories(minmd PUBLIC ${pkgs_INCLUDE_DIRS})
target_compile_options(minmd PUBLIC ${pkgs_CFLAGS_OTHER})
