cmake_minimum_required(VERSION 3.10)

get_filename_component(ProjectId $(CMAKE_CURRENT_SOURCE_DIR) NAME)
project($ProjectId)

set(CMAKE_CXX_COMPILER clang++)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_VERBOSE_MAKEFILE ON)

add_compile_options(
	-Wall
	-Werror
	-Wextra
	-pedantic
)


add_executable(main main.cc)
