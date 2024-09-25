# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.5.0)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Ballenger_GLFW_OpenGl4_Port")

# Include sub-projects.
add_subdirectory ("Ballenger_GLFW_OpenGl4_Port")


# copy level files to build directory
file(GLOB LEVELS
      "Levels/*.raw"
      "Levels/*.txt"
      "Levels/*.psd"
      "Levels/*.jpg"
      "Levels/*.json"
)

foreach(LEVEL ${LEVELS})
      if(WIN32)
            # configure_file(${LEVEL} "test")
            add_custom_command(TARGET ${NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${LEVEL} $<TARGET_FILE_DIR:${NAME}>)
      elseif(UNIX AND NOT APPLE)
            file(COPY ${LEVEL} DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}/Levels)
      elseif(APPLE)
            # create symbolic link for *.vs *.fs *.gs
            get_filename_component(LEVELNAME ${LEVEL} NAME)
            makeLink(${LEVEL} ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}/Levels/${LEVELNAME} ${NAME})
      endif(WIN32)
endforeach(LEVEL)

# copy model files to build directory
file(GLOB MODELS
      "Models/*.blend"
      "Models/*.obj"
)

foreach(MODEL ${MODELS})
      if(WIN32)
            # configure_file(${MODEL} "test")
            add_custom_command(TARGET ${NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${MODEL} $<TARGET_FILE_DIR:${NAME}>)
      elseif(UNIX AND NOT APPLE)
            file(COPY ${MODEL} DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}/Models)
      elseif(APPLE)
            # create symbolic link for *.vs *.fs *.gs
            get_filename_component(MODELNAME ${MODEL} NAME)
            makeLink(${MODEL} ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}/Models/${MODELNAME} ${NAME})
      endif(WIN32)
endforeach(MODEL)

# copy shader files to build directory
file(GLOB SHADERS
      "Shaders/*.vert"
      "Shaders/*.frag"
      "Shaders/*.geom"
)

foreach(SHADER ${SHADERS})
      if(WIN32)
            # configure_file(${SHADER} "test")
            add_custom_command(TARGET ${NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SHADER} $<TARGET_FILE_DIR:${NAME}>)
      elseif(UNIX AND NOT APPLE)
            file(COPY ${SHADER} DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}/Shaders)
      elseif(APPLE)
            # create symbolic link for *.vs *.fs *.gs
            get_filename_component(SHADERNAME ${SHADER} NAME)
            makeLink(${SHADER} ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}/Shaders/${SHADERNAME} ${NAME})
      endif(WIN32)
endforeach(SHADER)

# copy sound files to build directory
file(GLOB SOUNDS
      "Sounds/*.mp3"
      "Sounds/*.wav"
)

foreach(SOUND ${SOUNDS})
      if(WIN32)
            # configure_file(${SOUND} "test")
            add_custom_command(TARGET ${NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SOUND} $<TARGET_FILE_DIR:${NAME}>)
      elseif(UNIX AND NOT APPLE)
            file(COPY ${SOUND} DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}/Sounds)
      elseif(APPLE)
            # create symbolic link for *.vs *.fs *.gs
            get_filename_component(SOUNDNAME ${SOUND} NAME)
            makeLink(${SOUND} ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}/Sounds/${SOUNDNAME} ${NAME})
      endif(WIN32)
endforeach(SOUND)

# copy texture files to build directory
file(GLOB TEXTURES
      "Textures/*.png"
      "Textures/*.jpg"
      "Textures/skybox/*.jpg"
)

foreach(TEXTURE ${TEXTURES})
      if(WIN32)
            # configure_file(${TEXTURE} "test")
            add_custom_command(TARGET ${NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${TEXTURE} $<TARGET_FILE_DIR:${NAME}>)
      elseif(UNIX AND NOT APPLE)
            file(COPY ${TEXTURE} DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}/Textures)
      elseif(APPLE)
            # create symbolic link for *.vs *.fs *.gs
            get_filename_component(TEXTURENAME ${TEXTURE} NAME)
            makeLink(${TEXTURE} ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}/Textures/${TEXTURENAME} ${NAME})
      endif(WIN32)
endforeach(TEXTURE)







