cmake_minimum_required(VERSION 2.8.9)

project(myProject)


## #############################################################################
## Find medinria-superproject
## #############################################################################

find_package(medInria-superProject REQUIRED)
# From here the following libraries are found and can be use in your plugins:
#   -Qt
#   -ITK
#   -VTK
#   -TTK
#   -RPI
#   -QtDCM
#   -medinria


## #############################################################################
## Enable precompiled headers for Visual studio
## #############################################################################

if (MSVC)
  # Macros that enable precompiled headers to be added, defined by dtk.
  include(dtkPch)
  option(USE_PRECOMPILED_HEADERS "Use precompiled headers" ON)
endif(MSVC)


## #############################################################################
## Add your plugins
## #############################################################################

# call add_subdirectory for all plugins directory
add_subdirectory(myProjectDirectory)

  

