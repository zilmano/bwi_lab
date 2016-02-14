cmake_minimum_required(VERSION 2.8.3)
project(bwi_local)

find_package(catkin REQUIRED COMPONENTS roslint)
find_package(Boost REQUIRED COMPONENTS filesystem system)

catkin_package()

catkin_python_setup()

#############
## Install ##
#############

# NOTE: the "bwi" executable is installed directly in /usr/local/bin,
# and not in the usual ${CATKIN_PACKAGE_BIN_DESTINATION}.
install(PROGRAMS scripts/bwi
        RUNTIME DESTINATION bin)

set(${PROJECT_NAME}_PY_SCRIPTS scripts/distance_traveled)
catkin_install_python(PROGRAMS ${${PROJECT_NAME}_PY_SCRIPTS}
                      DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

install(PROGRAMS
          scripts/clone_server
          scripts/keygen
        DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

#############
## Testing ##
#############

# Lint Python modules
file(GLOB_RECURSE ${PROJECT_NAME}_PY_SRCS
     RELATIVE ${PROJECT_SOURCE_DIR} src/${PROJECT_NAME}/*.py)
roslint_python(${${PROJECT_NAME}_PY_SCRIPTS} ${${PROJECT_NAME}_PY_SRCS})

#if (CATKIN_ENABLE_TESTING)
#  add_subdirectory(tests)
#endif()