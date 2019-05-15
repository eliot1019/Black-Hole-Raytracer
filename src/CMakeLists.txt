cmake_minimum_required(VERSION 2.8)

# Application source
set(APPLICATION_SOURCE
        Program.cpp
        SchwarzschildBlackHoleEquation.h
        utils.h
        mappings/DiscMapping.h mappings/DiscMapping.cpp
        mappings/SphericalMapping.h mappings/SphericalMapping.cpp
        hitable/Disk.cpp hitable/Disk.h hitable/TexturedDisk.h
        hitable/Horizon.h hitable/Horizon.cpp hitable/Sky.h hitable/Sky.cpp
        hitable/TexturedDisk.cpp SchwarzschildRayProcessor.h SchwarzschildRayProcessor.cpp
        ThreadParams.h hitable/IHitable.h ArgbColor.cpp ArgbColor.h models/Matrix4x4.cpp models/Matrix4x4.h models/Vector4D.cpp models/Vector4D.h models/Vector3D.cpp models/Vector3D.h)

# Eliot: not sure about this
## Windows-only sources
#if(WIN32)
#    list(APPEND APPLICATION_SOURCE
#            # For get-opt
#            misc/getopt.c
#            )
#endif(WIN32)

#openCV
if(WIN32)
    set(OpenCV_DIR "c:/opencv/build/x64/vc14/lib")
else()
    set(OpenCV_DIR "/usr/lib/opencv")
endif()
find_package(OpenCV REQUIRED)

#-------------------------------------------------------------------------------
# Set include directories
#-------------------------------------------------------------------------------
include_directories(
        ${FREETYPE_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
)

#-------------------------------------------------------------------------------
# Set link directories
#-------------------------------------------------------------------------------
link_directories(
        ${FREETYPE_LIBRARY_DIRS}
)

#-------------------------------------------------------------------------------
# Add executable
#-------------------------------------------------------------------------------
add_executable(blackholetracer ${APPLICATION_SOURCE})

target_link_libraries( blackholetracer
        ${OPENGL_LIBRARIES}
        ${FREETYPE_LIBRARIES}
        ${CMAKE_THREADS_INIT}
        ${OpenCV_LIBS}
        )

#-------------------------------------------------------------------------------
# Platform-specific configurations for target
#-------------------------------------------------------------------------------
if(APPLE)
    set_property( TARGET blackholetracer APPEND_STRING PROPERTY COMPILE_FLAGS
            "-Wno-deprecated-declarations -Wno-c++11-extensions")
endif(APPLE)

# Put executable in build directory root
set(EXECUTABLE_OUTPUT_PATH ..)

# Install to project root
install(TARGETS blackholetracer RUNTIME DESTINATION bin DESTINATION ${BlackHoleTracer_SOURCE_DIR})
