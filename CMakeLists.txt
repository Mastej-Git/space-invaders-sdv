cmake_minimum_required(VERSION 3.10)

project(SpaceInvaders VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt5 REQUIRED COMPONENTS Charts)
find_package(Qt5 REQUIRED COMPONENTS Gamepad)
find_package(Qt5 REQUIRED COMPONENTS LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        src/main.cpp
        src/Player.cpp
        inc/Player.h
        src/Bullet.cpp
        inc/Bullet.h
        src/Enemy.cpp
        inc/Enemy.h
        src/Game.cpp
        inc/Game.h
        src/Score.cpp
        inc/Score.h
        src/Health.cpp
        inc/Health.h
        src/Flamethrower.cpp
        inc/Flamethrower.h
        src/Laser.cpp
        inc/Laser.h
        src/EnemyCyborg.cpp
        inc/EnemyCyborg.h
        src/EnemySentients.cpp
        inc/EnemySentients.h
        src/ComboBoxTxt.cpp
        inc/ComboBoxTxt.h
        src/ControllerManager.cpp
        inc/ControllerManager.h
        src/qcustomplot.cpp
        inc/qcustomplot.h
        src/AxisPlot.cpp
        inc/AxisPlot.h
        res.qrc
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SpaceInvaders
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SpaceInvaders APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(SpaceInvaders SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SpaceInvaders
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(SpaceInvaders PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(SpaceInvaders PRIVATE Qt${QT_VERSION_MAJOR}::Charts)
target_link_libraries(SpaceInvaders PRIVATE Qt${QT_VERSION_MAJOR}::Gamepad)

set_target_properties(SpaceInvaders PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS SpaceInvaders
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SpaceInvaders)
endif()
