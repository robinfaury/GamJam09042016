CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(EXE_NAME "GamJam")

PROJECT(${EXE_NAME})

SET(EXECUTABLE_OUTPUT bin / ${CMAKE_BUILD_TYPE})

FILE (GLOB_RECURSE sourceFiles src/*)

ADD_EXECUTABLE(${EXE_NAME} ${sourceFiles})

INCLUDE_DIRECTORIES("./ThirdParties/GLFW/include")
TARGET_LINK_LIBRARIES(${EXE_NAME} ../ThirdParties/GLFW/build/src/Debug/glfw3)
TARGET_LINK_LIBRARIES(${EXE_NAME} ../ThirdParties/GLFW/build/src/Release/glfw3)

INCLUDE_DIRECTORIES("./ThirdParties/GLEW/include")
TARGET_LINK_LIBRARIES(${EXE_NAME} ../ThirdParties/GLEW/lib/glew32)

INCLUDE_DIRECTORIES("./ThirdParties/GLM/include")

INCLUDE_DIRECTORIES("./ThirdParties/assimp/include")
TARGET_LINK_LIBRARIES(${EXE_NAME} ../ThirdParties/assimp/build/code/Debug/assimp-vc140-mt)
TARGET_LINK_LIBRARIES(${EXE_NAME} ../ThirdParties/assimp/build/code/Release/assimp-vc140-mt)

FIND_PACKAGE(OpenGL REQUIRED)
INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
if (OPENGL_FOUND)
	TARGET_LINK_LIBRARIES(${EXE_NAME} ${OPENGL_LIBRARIES})
endif()