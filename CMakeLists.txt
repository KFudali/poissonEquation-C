cmake_minimum_required(VERSION 3.8)

project(poissonEquation)
add_executable(poissonEquation src/poissonEquation.cpp)

find_package(VTK COMPONENTS 
  ChartsCore
  CommonColor
  CommonCore
  CommonDataModel
  InteractionStyle
  RenderingContext2D
  RenderingContextOpenGL2
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingOpenGL2
  ViewsContext2D
)

if (NOT VTK_FOUND)
  message(FATAL_ERROR "HighlightPickedActor: Unable to find the VTK build folder.")
endif()

set(CMAKE_NINJA_FORCE_RESPONSE_FILE "ON" CACHE BOOL "Force Ninja to use response files.")

target_link_libraries(poissonEquation PRIVATE ${VTK_LIBRARIES})
# vtk_module_autoinit is needed
vtk_module_autoinit(
  TARGETS poissonEquation
  MODULES ${VTK_LIBRARIES}
)

target_include_directories(poissonEquation  PUBLIC include)
target_link_directories(poissonEquation  PUBLIC src)
set_target_properties(poissonEquation PROPERTIES
    CXX_STANDARD 17
)
