# CMakeList.txt : CMake project for Ballenger_GLFW_OpenGl4_Port, include source and define
# project specific logic here.
#
find_package(glfw3 CONFIG REQUIRED)

if(WIN32)
find_package(glew CONFIG REQUIRED)
endif()

if(UNIX)
find_package(GLEW REQUIRED)
endif()

find_package(OpenGL REQUIRED)


include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIRS})


set(C_SOURCES "")

# add executables 
file(GLOB C_FILES
      "*.cpp"
      "*.h"
      "*.c"
)

foreach(C_FILE ${C_FILES})
  list(APPEND C_SOURCES
  ${C_FILE})
endforeach(MODEL)

add_executable(Ballenger_GLFW_OpenGl4_Port 
  ${C_SOURCES})


target_link_libraries(Ballenger_GLFW_OpenGl4_Port PRIVATE glfw ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Ballenger_GLFW_OpenGl4_Port PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
