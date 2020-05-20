project(G53GRA.Framework CXX)

cmake_minimum_required(VERSION 3.15)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "Code/MyScene.h"
    "Code/OnscreenText.h"
    "Framework/Engine/Engine.h"
    "Framework/Engine/Scene.h"
    "Framework/Interface/Animation.h"
    "Framework/Interface/DisplayableObject.h"
    "Framework/Interface/Input.h"
    "Framework/Utility/Camera.h"
    "Framework/Utility/Texture.h"
    "Framework/Utility/VectorMath.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "Code/main.cpp"
    "Code/MyScene.cpp"
    "Code/OnscreenText.cpp"
    "Framework/Engine/Engine.cpp"
    "Framework/Engine/Scene.cpp"
    "Framework/Utility/Camera.cpp"
    "Framework/Utility/Texture.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
        Code/Light.cpp Code/Light.h Code/Skybox/Skybox.cpp Code/Skybox/Skybox.h Code/Ocean/Ocean.cpp Code/Ocean/Ocean.h Code/OBJLoader/Model.cpp Code/OBJLoader/Model.h Code/OBJLoader/Utils.h Code/OBJLoader/Face.cpp Code/OBJLoader/Face.h Code/OBJLoader/Material.cpp Code/OBJLoader/Material.h Code/ModelGroups/PalmTree/PalmTree.cpp Code/ModelGroups/PalmTree/PalmTree.h Code/DayNight/Sun.cpp Code/DayNight/Sun.h Code/DayNight/Moon.cpp Code/DayNight/Moon.h Code/Projectile.cpp Code/Projectile.h)

set (CMAKE_CXX_FLAGS "-lGL -lGLU -lglut")

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

set(ROOT_NAMESPACE G53GRAFramework)

################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/Framework;"
    "${CMAKE_CURRENT_SOURCE_DIR}/Code;"
    "${CMAKE_CURRENT_SOURCE_DIR}/Code/Demos;"
    "${CMAKE_CURRENT_SOURCE_DIR}/Framework/Utility;"
    "${CMAKE_CURRENT_SOURCE_DIR}/Framework/Interface;"
    "${CMAKE_CURRENT_SOURCE_DIR}/Framework/Engine;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../freeglut/include"
)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "_MBCS"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /Od;
        /sdl;
        ${DEFAULT_CXX_DEBUG_RUNTIME_LIBRARY};
        /W3;
        /WX-;
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        ${DEFAULT_CXX_EXCEPTION_HANDLING}
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        /DEBUG
    )
endif()

target_link_libraries(
        ${PROJECT_NAME}
        ${OPENGL_gl_LIBRARY}
        ${GLUT_LIBRARIES} )


