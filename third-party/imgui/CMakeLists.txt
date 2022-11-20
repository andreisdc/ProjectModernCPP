cmake_minimum_required(VERSION 3.22)

project(imgui)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

set(IMGUI_SOURCES
		imgui.cpp
		imgui_draw.cpp
		imgui_tables.cpp
		imgui_widgets.cpp
		imgui_stdlib.cpp
		imgui_demo.cpp
		imgui_impl_sdl.cpp
		imgui_impl_opengl3.cpp)

set(IMGUI_HEADERS
		imconfig.h
		imgui.h
		imgui_internal.h
		imgui_impl_sdl.h
		imgui_impl_opengl3.h
		imgui_impl_opengl3_loader.h
		imgui_stdlib.h
		imstb_rectpack.h
		imstb_textedit.h
		imstb_truetype.h)

add_library(imgui STATIC
		${IMGUI_SOURCES}
		${IMGUI_HEADERS})

target_sources(imgui PRIVATE
		${IMGUI_SOURCES})

target_include_directories(imgui
		PUBLIC ${CMAKE_CURRENT_LIST_DIR}
		PUBLIC ${SDL2_INCLUDE_DIR}
		PUBLIC ${OPENGL_INCLUDE_DIR})

target_link_libraries(imgui PUBLIC
		${SDL2_LIBRARIES}
		${OPENGL_LIBRARIES})
