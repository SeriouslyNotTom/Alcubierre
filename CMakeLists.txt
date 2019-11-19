cmake_minimum_required (VERSION 3.8)
project(alcubierre VERSION 0.1.0.0) # MAJOR.MINOR.PATCH.TWEAK

SET(VERSION_TYPE "IDB") # "(I)n (D)evelopment (B)uild"
#SET(VERSION_TYPE "RCB") # "(R)elease (C)andidate (B)uild"
#SET(VERSION_TYPE "PVB") # "(P)re(V)iew (B)uild"

#PRONOUNCED: AL-KU-BEE-EHR, I always thought it was AL-QUE-BEE-REE
SET(GAME_STRING "Alcubierre")
string(TIMESTAMP PROJECT_BUILD_DATE "%Y-%m-%d")

include_directories("lib")
include_directories("src")
include_directories("include")

file(GLOB_RECURSE SRC
    "src/*.cpp"
	"src/*.h"
)

add_executable (${PROJECT_NAME} ${SRC})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/output/debug/)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output/debug/)
configure_file(${PROJECT_SOURCE_DIR}/src/config.h.in ${PROJECT_SOURCE_DIR}/src/config.h)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARY})

if(WIN32)
	#synthetic means being build on a platform that is not native to the build type
	#essentially used to build libs from source when crosscompilling on linux for win32, because linking prebuilt win32 stuff from linux suuuuuuuucks
	#the synthetic variable is set in /toolchains/window.cmake
	if(NOT SYNTHETIC)
	target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/win64/glfw3.lib)
	endif(NOT SYNTHETIC)
	target_link_libraries(${PROJECT_NAME} gdi32)
endif(WIN32)

if(UNIX)
	target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/linux/libsteam_api.so)
endif(UNIX)

IF(APPLE)

endif(APPLE)


#going to move this stuff below to sub directories cleaning everything up. making it easier to swap in and out modules

#glad (OpenGL 4.0, No Extensions) Might change this for linux builds as my ubuntu x230 crashes on init with gl4.0
set(GLAD_DIR "${PROJECT_SOURCE_DIR}/lib/src/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
include_directories(${GLAD_DIR}/include/)
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")

#lz4
set(LZ4_DIR "${PROJECT_SOURCE_DIR}/lib/src/lz4")
add_library("lz4" "${LZ4_DIR}/lz4.c")
target_include_directories("lz4" PRIVATE "${LZ4_DIR}")
target_include_directories(${PROJECT_NAME} PRIVATE "${LZ4_DIR}")
target_link_libraries(${PROJECT_NAME} "lz4")

#imgui
set(IMGUI_DIR "${PROJECT_SOURCE_DIR}/lib/src/imgui")
file(GLOB IMGUI_SRC
    ${IMGUI_DIR}/*.cpp
	${IMGUI_DIR}/*.h
)
add_library("imgui" ${IMGUI_SRC})
target_include_directories("imgui" PRIVATE ${IMGUI_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${IMGUI_DIR})
target_link_libraries(${PROJECT_NAME} "imgui")

#i'm sure there is a better way to do this but i cannot be fucked
#for some reason glfw3 wants to compile everything including macos and linux stuff even when being built from win32
add_definitions(-DGLFW_INCLUDE_NONE)
if(UNIX OR SYNTHETIC)
	set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

	add_subdirectory(${PROJECT_SOURCE_DIR}/lib/src/glfw-3.3)
	target_link_libraries(${PROJECT_NAME} glfw)
	set(CMAKE_C_FLAGS "-static-libstdc++ -static-libgcc -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic")
	set(CMAKE_CXX_FLAGS "-static-libstdc++ -static-libgcc -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic")
endif(UNIX)
