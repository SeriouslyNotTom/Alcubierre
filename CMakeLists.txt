cmake_minimum_required (VERSION 3.8)
project(alcubierre VERSION 0.1.0.0) # MAJOR.MINOR.PATCH.TWEAK

#set(CMAKE_BUILD_TYPE Debug)
string(TIMESTAMP PROJECT_BUILD_DATE "%Y-%m-%d")

SET(VERSION_TYPE "IDB") # "(I)n (D)evelopment (B)uild"
#SET(VERSION_TYPE "RCB") # "(R)elease (C)andidate (B)uild"
#SET(VERSION_TYPE "PVB") # "(P)re(V)iew (B)uild"

#PRONOUNCED: AL-KU-BEE-EHR, I always thought it was AL-QUE-BEE-REE
SET(GAME_STRING "Alcubierre")

#change these idiot
include_directories("lib")
include_directories("src")
include_directories("include")

include_directories("lib/src/imgui")

#include_directories("lib/src/tracy/profiler/libs/gl3w")

file(GLOB imgui_src
	lib/src/imgui/*.cpp
	lib/src/imgui/*.h
)

file(GLOB_RECURSE SRC 
	src/*.cpp 
	src/*.h 
	main.cpp
	main.h
	${imgui_src}
)

# Add source to this project's executable.
add_executable (${PROJECT_NAME} WIN32 ${SRC})

if(WIN32)
set_target_properties(${PROJECT_NAME} PROPERTIES 
LINK_FLAGS /SUBSYSTEM:WINDOWS
LINK_FLAGS /entry:mainCRTStartup
)
endif(WIN32)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
# versioning and maybe more stuff later
configure_file(${PROJECT_SOURCE_DIR}/src/config.h.in ${PROJECT_SOURCE_DIR}/src/config.h)


#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_SOURCE_DIR}/output/)

#i love that i can do this, idealy i want to implement everything below as cmake modules
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARY})


#platform linking
#idealy i want to replace these with source builds so no more platform errors
if(WIN32)
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/win64/glfw3.lib)
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/win64/freetype.lib)
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/win64/steam_api64.lib)
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/win64/DevIL.lib)
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/win64/ILU.lib)
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/win64/ILUT.lib)
target_link_libraries(${PROJECT_NAME} shcore)
endif(WIN32)

if(UNIX)
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/linux/libglfw.so.3)
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/linux/libsteam_api.so)
#	:(
target_link_libraries(${PROJECT_NAME} /usr/lib/x86_64-linux-gnu/libfreetype.so.6.15.0)
endif(UNIX)

#going to move this stuff below to sub directories cleaning everything up. making it easier to swap in and out modules

#glad (OpenGL 4.0, No Extensions) Might change this for linux builds as my ubuntu x230 crashes on init with gl4.0
set(GLAD_DIR "${PROJECT_SOURCE_DIR}/lib/src/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")

#lz4
set(LZ4_DIR "${PROJECT_SOURCE_DIR}/lib/src/lz4")
add_library("lz4" "${LZ4_DIR}/lz4.c")
target_include_directories("lz4" PRIVATE "${LZ4_DIR}")
target_include_directories(${PROJECT_NAME} PRIVATE "${LZ4_DIR}")
target_link_libraries(${PROJECT_NAME} "lz4")

#imgui
#set(IMGUI_DIR "${PROJECT_SOURCE_DIR}/lib/src/imgui")
#add_library("imgui" "${IMGUI_DIR}/")
#target_include_directories("imgui" PRIVATE "${IMGUI_DIR}")
#target_include_directories(${PROJECT_NAME} PRIVATE {"IMGUI_DIR"})
#target_link_libraries(${PROJECT_NAME} "imgui")




include_directories("${PROJECT_SOURCE_DIR}/lib/src/GameNetworkingSockets")
add_subdirectory("${PROJECT_SOURCE_DIR}/lib/src/GameNetworkingSockets")