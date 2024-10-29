cmake_minimum_required(VERSION 3.22)
project(pstme)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)

pkg_check_modules(LB_LIBS REQUIRED gtkmm-3.0)

add_executable(pstme src/main.cpp
	src/main_window.h
	src/main_window.cpp
	src/chunks.h src/chunks.cpp
	src/load_chunks.cpp
	src/load_chunks.h
	README.md
	src/tools.cpp
	src/tools.h)

include_directories(pstme ${LB_LIBS_INCLUDE_DIRS})
target_link_options(pstme PRIVATE ${LB_LIBS_LDFLAGS})
target_link_libraries(pstme ${LB_LIBS_LIBRARIES})

install(TARGETS pstme)
