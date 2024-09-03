cmake_minimum_required(VERSION 3.16)

project(hii VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt6 6.5 REQUIRED COMPONENTS Quick OpenGL)
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(apphii
    main.cpp
)
qt_add_qml_module(apphii
    URI hii
    VERSION 1.0
    QML_FILES
        Main.qml
        RESOURCES form.ui
)

set_target_properties(apphii PROPERTIES
    WIN32_EXECUTABLE TRUE
)
vtk_module_autoinit(
  TARGETS apphii
  MODULES ${VTK_LIBRARIES}
)

target_link_libraries(apphii
    PRIVATE Qt6::Quick
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
