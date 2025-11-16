cmake_minimum_required(VERSION 3.10)
project(CameraControlTest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(CameraControlTest main.cpp)

# Link libraries
target_link_libraries(CameraControlTest 
    CameraCtrl.lib
    strmiids
    Ws2_32
    ole32
    oleaut32
    Advapi32
)

# Copy DLL to output directory
add_custom_command(TARGET CameraControlTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_SOURCE_DIR}/CameraCtrl.dll
    $<TARGET_FILE_DIR:CameraControlTest>
)

# Include directories
target_include_directories(CameraControlTest PRIVATE ${CMAKE_SOURCE_DIR})

