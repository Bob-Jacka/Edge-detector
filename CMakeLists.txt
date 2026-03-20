cmake_minimum_required(VERSION 3.31)
project(Edge_detector)

add_compile_options(-Wall -Wextra)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include(FetchContent)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
set(CMAKE_DEFAULT_BUILD_TYPE "Debug" CACHE STRING "" FORCE)

message("Available configs: ${CMAKE_CONFIGURATION_TYPES}")
message("Default config: ${CMAKE_DEFAULT_BUILD_TYPE}")

if (WIN32)
    message("Declare opencv dependency")
    FetchContent_Declare(
            opencv
            GIT_REPOSITORY https://github.com/opencv/opencv
            GIT_TAG 4.13.0
    )

    message("Declare qt base dependency")
    FetchContent_Declare(
            qtbase
            GIT_REPOSITORY https://github.com/qt/qtbase
            GIT_TAG v6.10.2
    )

    message("Declare qt multimedia dependency")
    FetchContent_Declare(
            qtmultimedia
            GIT_REPOSITORY https://github.com/qt/qtmultimedia
            GIT_TAG v6.10.2
    )
endif ()

if (UNIX)
    message("Using system level libraries")
    find_package(OpenCV REQUIRED)
    find_package(Qt6 COMPONENTS
            Core
            Gui
            Widgets
            Multimedia
            MultimediaWidgets
            UiTools # for dynamic loading
            REQUIRED
    )
    include_directories(${OpenCV_INCLUDE_DIRS})
endif ()

add_executable(Edge_detector
        main.cpp
        edge_detector.ui

        libio.cppm
)

if (WIN32)
    FetchContent_MakeAvailable(opencv)
    FetchContent_MakeAvailable(qtbase)
    FetchContent_MakeAvailable(qtmultimedia)
endif ()

if (UNIX)
    message("Using UNIX target link")
    target_link_libraries(Edge_detector
            PRIVATE
            Qt6::Core
            Qt6::Widgets
            Qt6::Multimedia
            Qt6::MultimediaWidgets
            Qt6::UiTools # for dynamic loading

            opencv_core
            opencv_imgproc
            opencv_highgui
    )
endif ()

if (WIN32)
    message("Using Windows target link")
    target_link_libraries(Edge_detector
            PRIVATE
            qtbase
            qtmultimedia

            opencv_core
            opencv_imgproc
            opencv_highgui
    )
endif ()

target_sources(Edge_detector
        PUBLIC
        FILE_SET all_my_modules TYPE CXX_MODULES FILES
        libio.cppm
)