cmake_minimum_required(VERSION 3.14)
project(frc_dashboard)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ====== Include path ======
include_directories(
    $ENV{HOME}/wpilib/2025/cpp/include/ntcore
    $ENV{HOME}/wpilib/2025/cpp/include/wpinet
    $ENV{HOME}/wpilib/2025/cpp/include/wpiutil
)

# ====== Library search path ======
link_directories(
    $ENV{HOME}/wpilib/2025/cpp/osx
)

# ====== Source ======
add_executable(frc_dashboard
    src/main.cpp
)

# ====== Link WPILib C++ Desktop libs ======
target_link_libraries(frc_dashboard
    ntcore
    wpinet
    wpiutil
)

# ====== macOS の rpath ======
set_target_properties(frc_dashboard PROPERTIES
    BUILD_RPATH "$ENV{HOME}/wpilib/2025/cpp/osx"
    INSTALL_RPATH "$ENV{HOME}/wpilib/2025/cpp/osx"
)
