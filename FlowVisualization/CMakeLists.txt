
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(flowVisSample)

find_package(VTK COMPONENTS 
  CommonColor
  CommonCore
  CommonDataModel
  FiltersCore
  FiltersGeometry
  FiltersSources
  FiltersModeling
  IOImage
  IOLegacy
  ImagingCore
  InteractionStyle
  InteractionWidgets
  RenderingAnnotation
  RenderingContextOpenGL2
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingVolumeOpenGL2
  RenderingVolume
  RenderingOpenGL2
)

if (NOT VTK_FOUND)
  message(FATAL_ERROR "flowVisSample: Unable to find the VTK build folder.")
endif()

# Prevent a "command line is too long" failure in Windows.
set(CMAKE_NINJA_FORCE_RESPONSE_FILE "ON" CACHE BOOL "Force Ninja to use response files.")
add_executable(flowVisSample MACOSX_BUNDLE flowVisSample.cxx )
  target_link_libraries(flowVisSample PRIVATE ${VTK_LIBRARIES}
)
# vtk_module_autoinit is needed
vtk_module_autoinit(
  TARGETS flowVisSample
  MODULES ${VTK_LIBRARIES}
)
