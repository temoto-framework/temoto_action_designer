cmake_minimum_required(VERSION 2.8.12)
project(temoto_action_designer)

add_compile_options(-std=c++17)
find_package(temoto_action_engine REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets REQUIRED)

add_subdirectory(nodeeditor)

include_directories(
  include
)

add_executable(${PROJECT_NAME} 
  src/action_designer_main.cpp
)

target_link_libraries(${PROJECT_NAME}
  temoto_action_engine
)

qt5_use_modules(${PROJECT_NAME} Widgets)

file(GLOB_RECURSE CPPS ./src/node_editor_examples/*.cpp )
file(GLOB_RECURSE HPPS ./src/node_editor_examples/*.hpp )

add_executable(nodeeditor_test
  ${HPPS}
  ${CPPS}
)

target_link_libraries(nodeeditor_test
  QtNodes
)


