cmake_minimum_required(VERSION 3.5)

project(testOpenCV LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets Multimedia  REQUIRED)

if(ANDROID)
  add_library(testOpenCV SHARED
    main.cpp
    widget.cpp
    widget.h
    widget.ui
  )
else()
  add_executable(testOpenCV
    main.cpp
    widget.cpp
    widget.h
    widget.ui
    inference.cpp
    inference.h
    cameraworker.cpp
    cameraworker.h
    photoworker.cpp
    photoworker.h
    images.qrc
    logo/logo.rc

  )
endif()


include_directories("E:/opencv490SDK/opencv/build/include" "E:/opencv490SDK/opencv/build/include/opencv2")

target_link_libraries(testOpenCV PRIVATE Qt5::Widgets)

target_link_libraries(testOpenCV PRIVATE Qt5::Widgets Qt5::Multimedia "E:/opencv490SDK/opencv/build/x64/vc16/lib/opencv_world490.lib")

