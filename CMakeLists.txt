cmake_minimum_required(VERSION 3.31)
project(Editor)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_AUTOMOC ON)  # Enable AUTOMOC for Qt signals/slots
set(CMAKE_AUTORCC ON)  # Enable AUTORCC for resource files (not used here)
set(CMAKE_AUTOUIC ON)  # Enable AUTOUIC for .ui files

# Find required Qt packages
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

# List your source files and UI files
set(SOURCES
        src/main.cpp
        src/mainwindow.cpp
)

set(UI_FILES
        src/test.ui
)

# Add the executable
add_executable(Editor ${SOURCES} ${UI_FILES})

# Include the "includes" directory for header files
target_include_directories(Editor PRIVATE includes)

# Link Qt libraries to your executable
target_link_libraries(Editor
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

# Windows-specific DLL handling
if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_PREFIX_PATH "C:/Qt/6.8.2/mingw_64")
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
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()

# Install Qt DLLs (optional)
if (WIN32)
    install(FILES
            "$<TARGET_FILE:Qt6::Core>"
            "$<TARGET_FILE:Qt6::Gui>"
            "$<TARGET_FILE:Qt6::Widgets>"
            DESTINATION bin
    )
endif()