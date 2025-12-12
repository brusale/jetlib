#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 3.16...3.21)
project(jetlib)

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
