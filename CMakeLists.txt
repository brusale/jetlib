#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 3.16...3.21)
project(jetlib)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
#option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
#if(WITH_GEANT4_UIVIS)
#  find_package(Geant4 REQUIRED ui_all vis_all)
#else()
#  find_package(Geant4 REQUIRED)
#endif()
#
###----------------------------------------------------------------------------
### Setup Geant4 include directories and compile definitions
### Setup include directory for this project
###
#include(${Geant4_USE_FILE})
#message(STATUS "Geant4 use file: ${Geant4_USE_FILE}")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")
include_directories(${PROJECT_SOURCE_DIR}/interface)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED COMPONENTS RIO Net)
include("${ROOT_USE_FILE}")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include_directories(${ROOT_INCLUDE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${ROOT_INCLUDE_DIR} ${ROOTSYS})

#----------------------------------------------------------------------------
# Find Pyhia8 
#
find_package(Pythia8 REQUIRED)
include_directories(${PYTHIA8_INCLUDE_DIRS})
#----------------------------------------------------------------------------
# Find FastJet using fastjet-config
#
find_program(FASTJET_CONFIG fastjet-config PATHS /opt/fastjet-3.5.0/bin)
if(NOT FASTJET_CONFIG)
    message(FATAL_ERROR "fastjet-config not found")
endif()

# Get FastJet compilation flags
execute_process(COMMAND ${FASTJET_CONFIG} --cxxflags
                OUTPUT_VARIABLE FASTJET_CXX_FLAGS
                OUTPUT_STRIP_TRAILING_WHITESPACE)

# Get FastJet library flags
execute_process(COMMAND ${FASTJET_CONFIG} --libs
                OUTPUT_VARIABLE FASTJET_LIBRARIES
                OUTPUT_STRIP_TRAILING_WHITESPACE)

# Get FastJet include directory
execute_process(COMMAND ${FASTJET_CONFIG} --prefix
                OUTPUT_VARIABLE FASTJET_PREFIX
                OUTPUT_STRIP_TRAILING_WHITESPACE)

set(FASTJET_INCLUDE_DIR "${FASTJET_PREFIX}/include")
include_directories(${FASTJET_INCLUDE_DIR})

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/interface/*.h)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 and Python libraries
#

# Add the main.cc executable
add_executable(jetlib jetlib.cc ${sources} ${headers})
target_link_libraries(jetlib ${PYTHIA8_LIBRARIES} ${FASTJET_LIBRARIES} ${ROOT_LIBRARIES})

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#

# Install the main executable as well
install(TARGETS jetlib DESTINATION bin)
