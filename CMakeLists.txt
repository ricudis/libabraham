cmake_minimum_required(VERSION 3.9)

project(libabraham VERSION 1.0.1 DESCRIPTION "libabraham description")

execute_process(COMMAND date "+%u"
    OUTPUT_VARIABLE BUILD_DOW)
string(STRIP ${BUILD_DOW} BUILD_DOW)

include(GNUInstallDirs)

add_library(libabraham SHARED src/libabraham.c)

set_target_properties(libabraham PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER include/libabraham.h)

set_source_files_properties(src/libabraham.c
    PROPERTIES COMPILE_DEFINITIONS BUILD_DOW=\"${BUILD_DOW}\")

configure_file(libabraham.pc.in libabraham.pc @ONLY)

target_include_directories(libabraham PRIVATE .)

install(TARGETS libabraham
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES ${CMAKE_BINARY_DIR}/libabraham.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
