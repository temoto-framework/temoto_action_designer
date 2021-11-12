cmake_minimum_required(VERSION 2.8.12)
project(temoto_action_designer)

add_compile_options(-std=c++11)

add_subdirectory(temoto_action_engine/temoto_action_engine)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets REQUIRED)

include_directories(
  include
  temoto_action_engine/temoto_action_engine/include
)

add_executable(${PROJECT_NAME} 
  src/action_assistant_main.cpp
)

target_link_libraries(${PROJECT_NAME}
  temoto_action_engine
)

qt5_use_modules(${PROJECT_NAME} Widgets)

