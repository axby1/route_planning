#Cmake is cross platform build system generator
#CMakeLists.txt defines project structure, dependencies, instructions


cmake_minimum_required(VERSION 3.11.3) 

project(OSM_A_star_search)

set(CMAKE_CXX_STANDARD 17)

# Set CMake module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Locate Project Prerequisites (assuming they are installed externally)
find_package(io2d REQUIRED)  #graphics library for creating I/0-2D
find_package(Cairo)	     #graphics library for vector graphics(similar to io2d)
find_package(GraphicsMagick) #image processing 

# Find Google Test
find_package(GTest REQUIRED)	#for unit testing
include_directories(${GTEST_INCLUDE_DIRS})

# Find PugiXML using custom FindPugiXML.cmake
find_package(PugiXML REQUIRED)	#C++ XML processing library(R/W)
include_directories(${PUGIXML_INCLUDE_DIRS})

# Add Build Targets excluding sample applications and tests
set(IO2D_WITHOUT_SAMPLES 1)
set(IO2D_WITHOUT_TESTS 1)

# Find all source files
file(GLOB project_SRCS
    src/*.cpp
    src/*.h
)

# Add project executable target named(OSM_A_star_search) using source files collected in project_SRCS
add_executable(OSM_A_star_search ${project_SRCS})

# Link libraries to executable
target_link_libraries(OSM_A_star_search
    PRIVATE io2d::io2d #for internal use only(target)
    PUBLIC ${PUGIXML_LIBRARIES} ${GTEST_LIBRARIES} #libraries needed by other files than target
)

# Additional platform-specific configurations
if( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
    target_link_libraries(OSM_A_star_search PUBLIC pthread) #use POSIX Threading concepts when run on linux 
endif()

#for supressing warnings in MS VStudio 
if(MSVC) 
    target_compile_options(OSM_A_star_search PUBLIC /D_SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING /wd4459)
endif()

# Create a library for unit tests (assuming you have unit tests) (named route_planner) and use these files and directories
add_library(route_planner OBJECT src/route_planner.cpp src/model.cpp src/route_model.cpp)
target_include_directories(route_planner PRIVATE ${PUGIXML_INCLUDE_DIRS})

# Add testing executable target(tests) from source file(utest_rp_a_star_search.cpp) and link with GTest,route_planner,pugiXML libraries
add_executable(tests test/utest_rp_a_star_search.cpp)
target_link_libraries(tests gtest_main route_planner ${PUGIXML_LIBRARIES})
add_test(NAME tests COMMAND tests) #register tests executable as a test in Cmake testing framework(run using CTest)
