# Set the name and the supported language of the project
project(sampleapp C)

# Set the minimum version of cmake required to build this project
cmake_minimum_required(VERSION 2.6)

#include directories variables
include(GNUInstallDirs)

#include GSettings macro
include(GSettings.cmake)

#Directories in the source tree
set (SOURCE_SHARE "share")

##directories where to install files.
#These paths must be relative
set(GLIB_SCHEMADIR "glib-2.0/schemas")
set(SCHEMADIR      ${CMAKE_INSTALL_DATADIR}/${GLIB_SCHEMADIR})

set(RES_FILES "")

#compiled binary output directory
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#Make the binary directory
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

## Set the output binary full path name variable
set(OUTPUT_BIN ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})

#These path are passed onto config.h.in to be used as preprocessor definitions
if(MINGW)
  include(MinGW.cmake)
else()
  set(SHARE_DIR ${CMAKE_INSTALL_FULL_DATADIR})
  set(LOCALE_DIR ${CMAKE_INSTALL_FULL_LOCALEDIR})

  # at install, copy the software gschema.xml to the glib gschemas directory
  install(
    FILES ${SOURCE_SHARE}/${GLIB_SCHEMADIR}/${PROJECT_NAME}.gschema.xml
    DESTINATION ${GLIB_PREFIX}/${SCHEMADIR}
    )

  #at install, compile glib gschemas directory
  install(
    CODE
    "message (STATUS \"Compiling GSettings schemas at ${GLIB_PREFIX}/${SCHEMADIR}\")"
    )

  compile_schemas_install(${GLIB_PREFIX}/${SCHEMADIR})
endif()

#generate config.h from config.h.in
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/config.h)

# Use the package PkgConfig to detect GTK+ headers/library files
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
############################################################

# Add other flags to the compiler
add_definitions(${GTK3_CFLAGS_OTHER})
add_definitions(-Wall)

# files needed to compile the executable
add_executable(
  ${PROJECT_NAME}
  src/main.c
  src/app.c
  src/callbacks.c
  ${RES_FILES}   #resouces file for icon
  )

# Link the target to the GTK+ libraries
target_link_libraries(${PROJECT_NAME} ${GTK3_LIBRARIES} -lz)

# Compiler flag needed to reach callback functions
set(GCC_COVERAGE_COMPILE_FLAGS "-rdynamic")

## Install UI definitions files
install(
  FILES
  ${PROJECT_NAME}/ui/${PROJECT_NAME}.ui
  DESTINATION
  ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}/ui/
  )

## Install locales
###Français
install(
  FILES
  po/fr/${PROJECT_NAME}.mo
  DESTINATION ${CMAKE_INSTALL_LOCALEDIR}/fr/LC_MESSAGES/)

## Install icon
install(
  FILES ${PROJECT_NAME}/${PROJECT_NAME}.png
  DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME})

## Install desktop file
install(
  FILES ${PROJECT_NAME}.desktop
  DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)

## Install programs
install(PROGRAMS ${OUTPUT_BIN} DESTINATION ${CMAKE_INSTALL_BINDIR})
