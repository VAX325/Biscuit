cmake_minimum_required(VERSION 3.8)

cmake_policy(SET CMP0069 NEW)
include(CheckIPOSupported)
check_ipo_supported()

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_DEBUG")

file(GLOB SRC_FILES *.c)
add_executable (Biscuit ${SRC_FILES})
set_target_properties(Biscuit PROPERTIES C_STANDARD 11)
set_target_properties(Biscuit PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)

if(WIN32)
    set(APP_ICON_RESOURCE_WINDOWS "Resources/winRes.rc")
    target_sources(Biscuit PRIVATE ${APP_ICON_RESOURCE_WINDOWS})
endif()

target_precompile_headers(Biscuit PUBLIC pch.h)
