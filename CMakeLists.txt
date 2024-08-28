cmake_minimum_required(VERSION 3.16)

project(hii VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories("C:/VTKBin/lib/cmake/vtk-9.3")
find_package(Qt6 6.5 REQUIRED COMPONENTS Quick OpenGL)
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(apphii
    main.cpp
)
qt_add_library(VTK
    C:/VTKBin/lib
)
qt_add_qml_module(apphii
    URI hii
    VERSION 1.0
    QML_FILES
        Main.qml
)

# qt_add_library

set(VTKqml $ENV{VTK_DIR}/lib/qml/VTK.9.3)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(apphii PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.apphii
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
# add_library(vtk SHARED C:/VTKBin/lib)
message(${VTK_QML_DIR})
target_link_libraries(apphii
    PRIVATE Qt6::Quick
    #VTK::qmlvtkplugin
    ${QT_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${VTK_LIBRARIES}
)

include(GNUInstallDirs)
install(TARGETS apphii
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
