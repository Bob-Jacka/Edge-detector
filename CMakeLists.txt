cmake_minimum_required(VERSION 3.31)
project(Edge_detector)

add_compile_options(-Wall -Wextra)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
#set(OpenCV_DIR "C:/tools/opencv/sources")
include(FetchContent)

if (APPLE)
    message("Declare opencv dependency")
    FetchContent_Declare(
            opencv
            GIT_REPOSITORY https://github.com/opencv/opencv
            GIT_TAG 4.13.0
    )
endif ()

if (WIN32)
    message("Using windows aqtinstaller")
    set(CMAKE_PREFIX_PATH "C:/aqtinstaller/Qt/6.8.0/mingw_64") #TODO Look at this line in linux
endif ()

find_package(OpenCV REQUIRED)
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        REQUIRED
)

include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(Edge_detector
        main.cpp
        core/modulus/libio.cppm
        edge_detector.ui
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets Multimedia)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()

if (APPLE)
    FetchContent_MakeAvailable(opencv)
endif ()

target_include_directories(Edge_detector PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(Edge_detector
        PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Multimedia
        ${OpenCV_LIBS}
)

target_sources(Edge_detector
        PUBLIC
        FILE_SET all_my_modules TYPE CXX_MODULES FILES
        core/modulus/libio.cppm
)