cmake_minimum_required(VERSION 3.14)
project(frc_dashboard)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(/utf-8)
endif()

get_filename_component(UL_SDK_PATH "${CMAKE_CURRENT_SOURCE_DIR}/SDK" REALPATH)
list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/out" CACHE PATH "Install prefix" FORCE)
include(Common)

if(APPLE)
    set(WPILIB_ROOT "$ENV{HOME}/wpilib/2025/cpp")
elseif(WIN32)
    set(WPILIB_ROOT "C:/Users/Public/wpilib/2025/cpp")
endif()

link_directories(
    ${WPILIB_ROOT}/osx     # For macOS
    ${WPILIB_ROOT}/x86-64 # For Windows
)

set(SHOULD_EMBED_FILES FALSE)

set(SOURCE_FILES "src/MyApp.h"
                 "src/MyApp.cpp"
                 "src/main.cpp")

if (SHOULD_EMBED_FILES)
	set(SOURCE_FILES ${SOURCE_FILES}
					 "src/platform/EmbeddedFileSystem.h"
					 "src/platform/EmbeddedFileSystem.cpp")
    add_app(MyApp EMBED_FILES SOURCES ${SOURCE_FILES})
else ()
    add_app(MyApp SOURCES ${SOURCE_FILES})
endif ()

# ====== Link WPILib C++ Desktop libs to Ultralight app target ======
target_include_directories(MyApp PRIVATE
        ${WPILIB_ROOT}/include
        ${WPILIB_ROOT}/include/ntcore
        ${WPILIB_ROOT}/include/wpinet
        ${WPILIB_ROOT}/include/wpiutil
)

target_link_libraries(MyApp
    ntcore
    wpinet
    wpiutil
)

# ====== macOS rpath for WPILib when building on macOS ======
if(APPLE)
    # Frameworksディレクトリを作成
    add_custom_command(TARGET MyApp POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_FILE_DIR:MyApp>/../Frameworks"
    )

    # Ultralightのdylibをアプリバンドルにコピー
    set(UL_DYLIBS
            "${UL_SDK_PATH}/bin/libUltralight.dylib"
            "${UL_SDK_PATH}/bin/libUltralightCore.dylib"
            "${UL_SDK_PATH}/bin/libWebCore.dylib"
            "${UL_SDK_PATH}/bin/libAppCore.dylib"
    )

    foreach(dylib ${UL_DYLIBS})
        add_custom_command(TARGET MyApp POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${dylib}"
                "$<TARGET_FILE_DIR:MyApp>/../Frameworks/"
        )
    endforeach()

    # rpathを更新
    set_target_properties(MyApp PROPERTIES
            BUILD_RPATH "@executable_path/../Frameworks;$ENV{HOME}/wpilib/2025/cpp/osx"
            INSTALL_RPATH "@executable_path/../Frameworks;$ENV{HOME}/wpilib/2025/cpp/osx"
    )
endif()
