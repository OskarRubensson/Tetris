cmake_minimum_required(VERSION 3.10)
# set the projectX name to the name of your project
project(Tetris)

set(CMAKE_CXX_STANDARD 17)
# set(SOURCE_FILES main.cpp)

add_executable(Tetris main.cpp source/Window.cpp source/Window.h source/InputHandler.cpp source/InputHandler.h source/Game.cpp source/Game.h source/shapes/Shape.h source/shapes/Shape_SQR.cpp source/shapes/Shape_SQR.h source/shapes/Shape.cpp source/shapes/Shape_J.cpp source/shapes/Shape_J.h source/shapes/Shape_L.cpp source/shapes/Shape_L.h source/shapes/Shape_Z.cpp source/shapes/Shape_Z.h source/shapes/Shape_S.cpp source/shapes/Shape_S.h source/shapes/Shape_T.cpp source/shapes/Shape_T.h source/Clock.cpp source/Clock.h source/Grid.cpp source/Grid.h source/shapes/Shape_I.cpp source/shapes/Shape_I.h)
#add_executable(Window ${SOURCE_FILES})


# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()
