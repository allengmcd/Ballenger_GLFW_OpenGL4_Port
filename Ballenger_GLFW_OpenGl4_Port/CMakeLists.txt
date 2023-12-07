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


# Add source to this project's executable.
add_executable (Ballenger_GLFW_OpenGl4_Port 
  conio.h   
  ge_bicho.cpp  
  ge_bicho.h     
  ge_camera.h
  ge_data.cpp  
  ge_data.h  
  ge_filesystem.h
  ge_game.cpp 
  ge_game.h  
  ge_image.cpp  
  ge_image.h   
  ge_key.cpp  
  ge_key.h  
  ge_lava.cpp   
  ge_lava.h 
  ge_model.cpp 
  ge_model.h 
  ge_player.cpp 
  ge_player.h
  ge_scene.cpp 
  ge_scene.h
  ge_shader.cpp             
  ge_shader.h               
  ge_skybox.cpp             
  ge_skybox.h                 
  ge_terrain.cpp            
  ge_terrain.h              
  ge_texture.cpp            
  ge_texture.h              
  glad.c                    
  Globals.h                 
  main.cpp
  stb_image.h
)

target_link_libraries(Ballenger_GLFW_OpenGl4_Port PRIVATE glfw ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Ballenger_GLFW_OpenGl4_Port PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
