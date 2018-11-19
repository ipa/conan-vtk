cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0020 NEW)
PROJECT(test)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    execute_process(COMMAND conan install .. -s build_type=${CMAKE_BUILD_TYPE})
endif()
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
conan_basic_setup(TARGETS)

IF(CMAKE_BUILD_TYPE MATCHES Debug)
    SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} C:\\Develop\\lib\\src\\conan-vtk\\tmp\\debug\\package\\lib\\cmake)
ELSE()
    SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} C:\\Develop\\lib\\src\\conan-vtk\\tmp\\release\\package\\lib\\cmake)
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)

message(${CMAKE_PREFIX_PATH})
#set(VTK_DIR C:/Develop/lib/src/conan-vtk/tmp/release/package/lib/cmake/vtk-8.1)
#SET(VTK_INCLUDE_DIRS ${VTK_DIR}/include/vtk-8.1)
#SET(VTK_LIBRARY_DIRS ${VTK_DIR}/lib)
#SET(VTK_LIBRARIES vtkRenderWindow-8.1)


add_executable(test main.cpp )
#link_directories(${VTK_LIBRARY_DIRS})
target_link_libraries(test PRIVATE ${CONAN_LIBS_VTK})

add_executable(scenegraphtest scenegraphtest.cpp )
#link_directories(${VTK_LIBRARY_DIRS})
target_link_libraries(scenegraphtest PRIVATE ${CONAN_LIBS_VTK})
