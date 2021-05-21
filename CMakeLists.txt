##############################################################################
# CMAKE CONFIGURATION
##############################################################################
cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

# set project name
project(polar-grid-dbscan-seg VERSION 1.0.3)

# set build type = Debug mode
set(CMAKE_BUILD_TYPE Debug)

# print build message
message("\n" "=========================================")
message("Project: ${PROJECT_NAME} ")
message("=========================================")

# set the include directive in the same project folder
set(CMAKE_INCLUDE_CURRENT_DIR ON)


# set cmake for use std c++11 and output executable folder to bin
#set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

##############################################################################
# PACKAGES
##############################################################################
message("***********************")
message("PCL PACKAGE")
message("***********************")

##find_package
find_package(PCL REQUIRED)
find_package(Eigen3 REQUIRED)
# 增加PCL库的依赖
find_package(Boost REQUIRED COMPONENTS system iostreams)
##############################################################################
# HEADERS
##############################################################################
include_directories(${PCL_INCLUDE_DIRS})
include_directories(${EIGEN3_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
# include_directories("/usr/local/include/vtk-9.0") 
# include(CheckFunctionExists)

# Use the compile definitions defined in PCL
add_definitions(${PCL_DEFINITIONS})

##############################################################################
# SOURCE CODE
##############################################################################
list(APPEND SOURCE_FILES "main.cpp"	
						 "src/dataToGrid.cpp"
						 "src/dbscan.cpp"
						 "src/groundRemove.cpp"
                         "src/lodaData.cpp"
						 "src/viewer.cpp"
)



##############################################################################
# ADD LIBRARIES PATH
##############################################################################
# add_library(project_shared SHARED ${SOURCE_FILES})


##############################################################################
# LIBRARIES PATH
##############################################################################
link_directories(${PCL_LIBRARY_DIRS})


##############################################################################
# EXECUTABLES
##############################################################################
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

##############################################################################
# TARGET LIBRARIES
##############################################################################
target_link_libraries(${PROJECT_NAME} ${PCL_LIBRARIES})

message("=========================================")
message("Project: ${PROJECT_NAME} COMPILED WITH CMAKE " ${CMAKE_VERSION})
message("=========================================")

