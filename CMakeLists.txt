cmake_minimum_required(VERSION 3.0)
project(boottest)
message( "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}" )
message( "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}" )
set( BOOST_DIR /c4_working/bug_fix_orsprey/infrastructureproviders/obj/KHDATAPATH_DEBUG/rpm_install/usr)
include_directories(${BOOST_DIR}/include)
#include_directories(/c4_working/bug_fix_orsprey/cp/obj/KITTYHAWK_DEBUG/rpm_install/usr/include/lib)
set(BOOST_ROOT ${BOOST_DIR}/include)
message("boost root: {${BOOST_ROOT}")
set(BOOST_INCLUDEDIR ${BOOST_DIR}/include)
set(BOOST_LIBRARYDIR ${BOOST_DIR}/lib64 )
message("boost lib: ${BOOST_LIBRARYDIR}")
set(Boost_THREAD_LIBRARY ${BOOST_DIR}/lib64/libboost_thread.so)
message("boost thread lib: ${Boost_THREAD_LIBRARY}")
set(Boost_FILESYSTEM_LIBRAR ${BOOST_DIR}/lib64/libboost_filesystem.so)
message("boost fs  lib: ${Boost_FILESYSTEM_LIBRAR}")
set(Boost_SYSTEM_LIBRARY ${BOOST_DIR}/lib64/libboost_system.so)
#set(BOOST_INCLUDEDIR /opt/boost/include/)
#set(BOOST_LIBRARYDIR /opt/boost/lib)
#set(Boost_NO_SYSTEM_PATHS TRUE)
#set(Boost_NO_BOOST_CMAKE TRUE)

#find_package(Boost REQUIRED
#    COMPONENTS regex
#    thread
#    system
#    filesystem
#    program_options
#    date_time
#    iostreams
#    unit_test_framework
#    serialization
#    chrono
#    )
#

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")


add_executable (bootDemo demo.cxx)
target_include_directories (bootDemo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(bootDemo 
    ${Boost_THREAD_LIBRARY}
    ${Boost_FILESYSTEM_LIBRAR}
    ${Boost_SYSTEM_LIBRARY}
)
