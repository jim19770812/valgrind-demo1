cmake_minimum_required(VERSION 3.24)
project(valgrind_demo1 C)

cmake_minimum_required(VERSION 3.22.1)
project(valgrind_demo1 C)
#add_compile_options(-E4C_THREADSAFE)

find_package(PkgConfig REQUIRED)

cmake_minimum_required(VERSION 3.24)
project(valgrind_demo1 C)
#set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD 99)
add_compile_options(-O0)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GLIB REQUIRED glib-2.0)
pkg_check_modules(ATSPI REQUIRED atspi-2)
pkg_check_modules(GOBJECT REQUIRED gobject-2.0)
pkg_check_modules(PC_ATK_BRIDGE REQUIRED atk-bridge-2.0)
pkg_check_modules(DBUS REQUIRED dbus-1)
pkg_check_modules(WNCK REQUIRED libwnck-3.0)
add_compile_options(-O0 -g)

include_directories(${GLIB_INCLUDE_DIRS})
include_directories(${ATSPI_INCLUDE_DIRS})
include_directories(${GOBJECT_INCLUDE_DIRS})
include_directories(${PC_ATK_BRIDGE_INCLUDE_DIRS})
include_directories(${DBUS_INCLUDE_DIRS})
include_directories(${WNCK_INCLUDE_DIRS})

link_directories(${GLIB_LIBRARY_DIRS})
link_directories(${ATSPI_LIBRARY_DIRS})
link_directories(${GOBJECT_LIBRARY_DIRS})
link_directories(${PC_ATK_BRIDGE_LIBRARY_DIRS})
link_directories(${DBUS_LIBRARY_DIRS})
link_directories(${WNCK_LIBRARY_DIRS})

add_definitions(${GLIB_CFLAGS_OTHER})
add_definitions(${ATSPI_CFLAGS_OTHER})
add_definitions(${GOBJECT_CFLAGS_OTHER})
add_definitions(${PC_ATK_BRIDGE_CFLAGS_OTHER})
add_definitions(${DBUS_CFLAGS_OTHER})
add_definitions(${WNCK_CFLAGS_OTHER})

add_executable(valgrind_demo1 main.c)
target_link_libraries(valgrind_demo1 ${GLIB_LIBRARIES} ${ATSPI_LIBRARIES} ${GOBJECT_LIBRARIES} ${PC_ATK_BRIDGE_LIBRARIES} ${DBUS_LIBRARIES} ${WNCK_LIBRARIES})
