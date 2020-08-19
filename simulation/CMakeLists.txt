# $Id: CMakeLists.txt 86065 2014-11-07 08:51:15Z gcosmo $

#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(OFOS)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#

#set(CMAKE_PREFIX_PATH /cm/shared/apps/tbb/2020.3/cmake/TBBMakeConfig.cmake)
#find_package(TBB REQUIRED)

#find_package(TBB REQUIRED)

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)

if (WITH_GEANT4_UIVIS)
    find_package(Geant4 REQUIRED ui_all vis_all)
else ()
    find_package(Geant4 REQUIRED)
endif ()
set(CMAKE_PREFIX_PATH /home/geant)
#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

#list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
#find_package(ROOT REQUIRED COMPONENTS)
#include(${ROOT_USE_FILE})
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
#ROOT_GENERATE_DICTIONARY(G__Event Event.h LINKDEF EventLinkDef.h)

#list(APPEND CMAKE_PREFIX_PATH $ENV{LD_LIBRARY_PATH})
#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs

### including ROOT Headers
EXECUTE_PROCESS(COMMAND root-config --cflags OUTPUT_VARIABLE ROOT_CXX_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_C_FLAGS "${ROOT_C_FLAGS} -Og -g3 -fno-omit-frame-pointer -ltbb")
    set(CMAKE_CXX_FLAGS "${ROOT_CXX_FLAGS} -Og -g3 -fno-omit-frame-pointer -ltbb")
else ()
    set(CMAKE_C_FLAGS "${ROOT_C_FLAGS} -O3 -march=native -ltbb")
    set(CMAKE_CXX_FLAGS "${ROOT_CXX_FLAGS} -O3 -march=native -ltbb")
endif ()


### standard G4
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh, ${PROJECT_SOURCE_DIR}/include/*.h, ${PROJECT_SOURCE_DIR}/include/*.icc)


#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(ofos ofos.cc ${sources} ${headers})

### including ROOT libraries

EXECUTE_PROCESS(COMMAND root-config --libs OUTPUT_VARIABLE ROOT_LD_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
set(CMAKE_EXE_LINKER_FLAGS ${ROOT_LD_FLAGS})
#message("${ROOT_LD_FLAGS}")

### standard G4
target_link_libraries(ofos ${Geant4_LIBRARIES})
target_link_libraries(ofos ${TBB_LIBRARIES})

### other root stuff
set(CMAKE_PREFIX_PATH ${ROOTSYS})
find_package(ROOT REQUIRED COMPONENTS)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
###ROOT_GENERATE_DICTIONARY(G__Event Event.h LINKDEF EventLinkDef.h)
target_link_libraries(ofos ${ROOT_LIBRARIES})
include(${ROOT_USE_FILE})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build ofos. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(SOME_SCRIPTS
        run.png
        gui.mac
        icons.mac
        init_vis.mac
        vis.mac
        shoot_positron.mac
        clearData.sh
        )


#set(CMAKE_BUILD_TYPE Debug)

foreach (_script ${SOME_SCRIPTS})
    configure_file(
            ${PROJECT_SOURCE_DIR}/utils/${_script}
            ${PROJECT_BINARY_DIR}/${_script}
            COPYONLY
    )
endforeach ()

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS ofos DESTINATION bin)
