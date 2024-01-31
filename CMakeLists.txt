cmake_minimum_required(VERSION 3.20)

project(poissonEquation)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#======================= Setting all sources variables ======================#

set(UI_DIR ${PROJECT_SOURCE_DIR}/UI)
set(ENGINE_DIR ${PROJECT_SOURCE_DIR}/engine)

set(EGNINE_SRC  ${ENGINE_DIR}/src/linearSolvers.cpp
                ${ENGINE_DIR}/src/plotContour.cpp
                ${ENGINE_DIR}/src/main.cpp)

set(EGNINE_HEADERS  ${ENGINE_DIR}/include/linearSolvers.hpp
                    ${ENGINE_DIR}/include/plotContour.hpp
                    ${ENGINE_DIR}/include/matrix.hpp)

set(UI_SRC  ${UI_DIR}/src/mainwindow.cpp)

set(UI_HEADERS    ${UI_DIR}/include/mainwindow.hpp
                  ${UI_DIR}/include/Forms/mainwindow.ui)

set(CMAKE_AUTOUIC_SEARCH_PATHS  ${CMAKE_AUTOUIC_SEARCH_PATHS} 
                                ${UI_DIR}/include/Forms
                                ${UI_DIR}/include/)

set(PROJECT_SOURCES ${EGNINE_SRC}
                    ${EGNINE_HEADERS}
                    ${UI_SRC}
                    ${UI_HEADERS})
                    
set(INCLUDE_DIRS 
  ${PROJECT_SOURCE_DIR}/engine/include
  ${PROJECT_SOURCE_DIR}/UI/include/Forms
  ${PROJECT_SOURCE_DIR}/UI/include)


#============ Print includes and sources for debug ==============#

# foreach(source ${PROJECT_SOURCES})
#   message(STATUS "SOURCE: ${source}")
# endforeach()

# foreach(dir ${INCLUDE_DIRS})
#   message(STATUS "INCLUDE_DIR: ${dir}")
# endforeach()

#======================= INCLUSION OF OpenGL ===================#

find_package(OpenGL QUIET)

#======================= INCLUSION OF QT6 ======================#
set(QT_COMPONENTS   Widgets 
                    OpenGLWidgets 
                    Core
                    Gui)

find_package(Qt6 REQUIRED COMPONENTS 
  ${QT_COMPONENTS}
)

#======================= INCLUSION OF VTK ======================#
find_package(VTK REQUIRED COMPONENTS
  CommonColor
  CommonCore
  FiltersSources
  InteractionStyle
  InteractionWidgets
  RenderingContextOpenGL2
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingOpenGL2
  GUISupportQt
  RenderingQt
  ViewsContext2D
  RenderingContext2D
  CommonDataModel
  ChartsCore
)

if(NOT(TARGET VTK::GUISupportQt))
  message(FATAL_ERROR "BorderWidgetQt: VTK not built with Qt support.")
endif()

find_package(Qt${VTK_QT_VERSION} REQUIRED COMPONENTS 
            ${QT_COMPONENTS}
)

#=======================Check QT and VTK Versions ==============#

message (STATUS "VTK_VERSION: ${VTK_VERSION}")
message (STATUS "QT_VERSION: ${Qt${VTK_QT_VERSION}Widgets_VERSION}")

#======================= Add executalbes ======================#

add_executable(poissonEquation
  ${PROJECT_SOURCES}
)
#======================= Link libraries ======================#
target_link_libraries(poissonEquation PRIVATE Qt6::OpenGL)
target_link_libraries(poissonEquation PRIVATE Qt6::Core)
target_link_libraries(poissonEquation PRIVATE Qt6::OpenGLWidgets)
target_link_libraries(poissonEquation PRIVATE Qt6::Gui)
target_link_libraries(poissonEquation PRIVATE ${QT_LIBRARIES} ${OPENGL_LIBRARIES})
target_link_libraries(poissonEquation PRIVATE ${VTK_LIBRARIES})


target_include_directories(poissonEquation PRIVATE ${INCLUDE_DIRS})


vtk_module_autoinit(
  TARGETS poissonEquation
  MODULES ${VTK_LIBRARIES}
)

