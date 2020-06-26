cmake_minimum_required(VERSION 3.4.0)

project(wolf3d CXX)

include(cmake/Settings.cmake)

add_executable(main src/client/main.cpp)

target_include_directories(main PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(main)

set(SFML_STATIC_LIBRARIES True)
set(SFML_DIR "C:/libs/SFML/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(main
	sfml-system sfml-window sfml-graphics sfml-network sfml-audio
)

find_package(OpenGL REQUIRED)
if(NOT OpenGL_FOUND)
	message(FATAL_ERROR "OpenGL not found")
endif()
target_include_directories(main
	PUBLIC ${OPENGL_INCLUDE_DIRS}
)
target_link_libraries(main
	${OPENGL_LIBRARIES}
)

target_link_libraries(main
	-static-libgcc -static-libstdc++ -lwsock32 -lws2_32
	-Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive
)

file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})

file(GLOB BINARY_DEP_DLLS "${CMAKE_SOURCE_DIR}/bin/*.dll")
file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})