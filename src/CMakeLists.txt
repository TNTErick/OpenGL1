
cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(XY_OpenGL_core LANGUAGES CXX)

message("Starting Processing src/\n\n")
get_filename_component(PARENT_DIR ".." REALPATH)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# hack for buggy CMake's FindwxWidgets script
if(DEFINED ENV_WX_CONFIG)
    set(ENV{WX_CONFIG} ${ENV_WX_CONFIG})
endif()

set(wxWidgets_USE_STATIC 1)

find_package(wxWidgets COMPONENTS core base gl REQUIRED)

set(GLEW_USE_STATIC_LIBS ON)
find_package(GLEW REQUIRED CONFIG)

#set(STAGED_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/../build/stage")
#file(COPY "${STAGED_INSTALL_PREFIX}/lib/Debug/*.lib" "${STAGED_INSTALL_PREFIX}/lib/Release/*" DESTINATION "${STAGED_INSTALL_PREFIX}/lib")

# the compiled files here.
list(APPEND SRCS
${CMAKE_CURRENT_LIST_DIR}/MyApp.cpp
${CMAKE_CURRENT_LIST_DIR}/MyWindow.cpp
${CMAKE_CURRENT_LIST_DIR}/MyGLCanvas.cpp
${CMAKE_CURRENT_LIST_DIR}/MyCamera.cpp
${CMAKE_CURRENT_LIST_DIR}/MyDebugWindow.cpp
)

include(xy/CMakeLists.txt)

include(${wxWidgets_USE_FILE})
include_directories(main PRIVATE "${PARENT_DIR}/thirdparty/glm")

if(APPLE)
    # create bundle on apple compiles
    add_executable(main MACOSX_BUNDLE ${SRCS})

    # Set a custom plist file for the app bundle - needed for Mac OS Retina display
    set_target_properties(main PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist)
else()
    # the WIN32 is needed for Windows in order for it to look for WinMain
    # instead of the main function. This is ignored on other systems,
    # so it works on all platforms
    add_executable(main WIN32 ${SRCS} main.exe.manifest)
endif()

target_link_libraries(main PRIVATE ${wxWidgets_LIBRARIES} GLEW::glew_s glm)

#temporarily copy by hand instead of auto-detect.

message("COPYING FILES RN DONT INTERRUPT")
#file(COPY "${PARENT_DIR}/build/stage/lib/Debug/glm.*" DESTINATION "${PARENT_DIR}/build/stage/lib")
#file(COPY "${PARENT_DIR}/build/stage/lib/Debug/glm.*" DESTINATION "${CMAKE_BINARY_DIR}")