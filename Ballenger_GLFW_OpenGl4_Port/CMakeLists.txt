# CMakeList.txt : CMake project for Ballenger_GLFW_OpenGl4_Port, include source and define
# project specific logic here.
#

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

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Ballenger_GLFW_OpenGl4_Port PROPERTY CXX_STANDARD 20)
endif()



if(WIN32)
find_package(glew CONFIG REQUIRED)
endif()

if(UNIX)
find_package(GLEW REQUIRED)
endif()

find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(ImageMagick REQUIRED COMPONENTS Magick++)
find_package(nlohmann_json REQUIRED)

target_compile_definitions(Ballenger_GLFW_OpenGl4_Port PRIVATE
  MAGICKCORE_QUANTUM_DEPTH=16
  MAGICKCORE_HDRI_ENABLE=0
)

include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${ImageMagick_INCLUDE_DIRS})


execute_process(COMMAND Magick++-config --ldflags
  OUTPUT_VARIABLE ImageMagick_LINK_FLAGS
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

target_link_libraries(Ballenger_GLFW_OpenGl4_Port PRIVATE 
  glfw 
  ${GLEW_LIBRARIES} 
  ${OPENGL_LIBRARIES} 
  ${ImageMagick_LIBRARIES} 
  nlohmann_json::nlohmann_json 
  /home/allenmcdermott/Documents/Development/Ballenger/Ballenger_GLFW_OpenGL4_Port/Ballenger_GLFW_OpenGl4_Port/libfmod.so)

# TODO: Add tests and install targets if needed.
