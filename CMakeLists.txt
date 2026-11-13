
cmake_minimum_required(VERSION 3.14)

# ============================================================
# 1. Project
# ============================================================

project(
    FPGA-Accelerated-Gesture-Recognition
    VERSION 1.0.0
    DESCRIPTION "USB Host with libusb and OpenCV"
    LANGUAGES C CXX
)

# ============================================================
# 2. C / C++ standards
# ============================================================

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ============================================================
# 3. Build type
# ============================================================

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# ============================================================
# 4. OpenCV
# ============================================================

set(OpenCV_DIR
    "C:/msys64/mingw64/lib/cmake/opencv5"
    CACHE PATH "OpenCV directory"
)

find_package(OpenCV REQUIRED)

message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")

# ============================================================
# 5. Directories
# ============================================================

set(PROJECT_INCLUDE_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/inc"
)

set(LIBUSB_INCLUDE_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libusb/inc"
)

set(LIBUSB_LIBRARY
    "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libusb/lib/libusb-1.0.a"
)

# ============================================================
# 6. Source files
# ============================================================

set(PROJECT_SOURCES
    src/main.cpp
)

# ============================================================
# 7. Executable
# ============================================================

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
)

# ============================================================
# 8. Include directories
# ============================================================

target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_INCLUDE_DIR}
    ${LIBUSB_INCLUDE_DIR}
    ${OpenCV_INCLUDE_DIRS}
)

# ============================================================
# 9. Link libraries
# ============================================================

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${LIBUSB_LIBRARY}
    ${OpenCV_LIBS}

    # Windows system libraries required by libusb
    setupapi
    ole32
    advapi32
)

# ============================================================
# 10. Compiler warnings
# ============================================================

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

# ============================================================
# 11. Debug configuration
# ============================================================

target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Debug>:-O0>
    $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
)

# ============================================================
# 12. Output directory
# ============================================================

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

# ============================================================
# 13. Testing
# ============================================================

enable_testing()

# ============================================================
# 14. Configuration summary
# ============================================================

message(STATUS "----------------------------------------")
message(STATUS "Configuration completed")
message(STATUS "Compiler C:   ${CMAKE_C_COMPILER}")
message(STATUS "Compiler C++: ${CMAKE_CXX_COMPILER}")
message(STATUS "C standard:   C11")
message(STATUS "C++ standard: C++17")
message(STATUS "OpenCV:       ${OpenCV_VERSION}")
message(STATUS "libusb:       enabled")
message(STATUS "----------------------------------------")
