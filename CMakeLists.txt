cmake_minimum_required(VERSION 3.0)

project(SimpleNodeStateMachine)

find_package(PkgConfig)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

pkg_check_modules (GLIB2 REQUIRED glib-2.0)
include_directories(${GLIB2_INCLUDE_DIRS})

pkg_check_modules (GIO REQUIRED gio-2.0)
include_directories(${GIO_INCLUDE_DIRS})

pkg_check_modules (GIO_UNIX REQUIRED gio-unix-2.0)
include_directories(${GIO_UNIX_INCLUDE_DIRS})

pkg_check_modules (NSM REQUIRED node-state-manager)
include_directories(${NSM_INCLUDE_DIRS})

pkg_search_module(IVILOGGING ivi-logging)
if(IVILOGGING_FOUND)
    add_definitions(${IVILOGGING_CFLAGS_OTHER})
    include_directories(${IVILOGGING_INCLUDE_DIRS})
endif()

add_library(NodeStateMachine SHARED
    "src/simplenodestatemachine.cpp"
)

target_link_libraries(NodeStateMachine
    ${IVILOGGING_LIBRARIES}
    ${NSM_LIBRARIES}
)

install(
    TARGETS NodeStateMachine
    LIBRARY DESTINATION lib
)
