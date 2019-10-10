cmake_minimum_required (VERSION 3.8)
project(Cwapy)

# Add the pybind subdir.
add_subdirectory(pybind11)

# Create our library.
add_library (Cwapy SHARED "src/main.cpp")

# Link pybind and CWTCore.
target_link_libraries (Cwapy PRIVATE pybind11::embed)
target_link_libraries (Cwapy LINK_PUBLIC CWTCore)

# Add the CWTCore includes.
target_include_directories (Cwapy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../CWTCore/include)