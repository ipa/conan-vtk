project(cmake_wrapper)

set(CMAKE_PREFIX_PATH "C:/Develop/toolchains/Qt/Qt5.10.1/5.10.1/msvc2017_64")

if(MSVC)
    # Remove pdb-related flags
    string(REGEX REPLACE "/Z[iI7]" ""
        CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    # Embed debug info into .lib-files
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} /Z7")
endif()

add_subdirectory(VTK-8.1.0)
