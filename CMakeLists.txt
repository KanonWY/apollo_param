cmake_minimum_required(VERSION 3.16)

# some option
option(GEN_SHARED_LIB "generate shared lib: default ON" ON)
option(GEN_STATIC_LIB "generate static lib: default OFF" OFF)
option(USE_EXAMPLE "compile example program: default ON" ON)
option(USE_CLANG "use clang to compile program: default OFF" OFF)

# compiler choose
if (USE_CLANG)
    set(CMAKE_ASM_COMPILER clang)
    set(CMAKE_C_COMPILER clang)
    set(CMAKE_CXX_COMPILER clang++)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=lld")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fuse-ld=lld")
    # speed gdb time
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-gdb-index")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-gdb-index")
else ()
    set(CMAKE_ASM_COMPILER gcc)
    set(CMAKE_C_COMPILER gcc)
    set(CMAKE_CXX_COMPILER g++)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=gold")
endif ()

# check arch
if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "aarch64")
    set(IS_ARM TRUE)
elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64")
    set(IS_ARM FALSE)
endif()


project(Apollo_CPP_Client LANGUAGES CXX C)

# set cpp 11 standard not allow extension
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# set cpp file extension name
set(CPP_HEADER_EXT "*.h" "*.hpp" "*.hrp" "*.hxx")
set(CPP_SOURCE_EXT "*.cpp" "*.cxx" "*.cc")
set(C_SOURCE_EXT "*.c")


#  compiler flag
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_FILE_OFFSET_BITS=64 -D__STDC_FORMAT_MACROS")
# speed compile
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe")

# default use release
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
            "choose the type of build, default use Release"
            FORCE)
endif ()


# compiler
include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported)
if (ipo_supported)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION True)
endif ()


# set gen dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/release/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/release/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/release/arc")


find_package(cpprestsdk REQUIRED)
find_package(spdlog REQUIRED)
find_package(yaml-cpp REQUIRED)


if (GEN_SHARED_LIB)
    add_library(apollo_client
            src/apollo_base.cpp
            src/apollo_url.cpp
            src/apollo_request.cpp
            src/apollo_openapi_client.cpp
            src/apollo_response.cpp
            src/apollo_yaml_tmp.cpp
            )
    if(IS_ARM)
        target_link_libraries(apollo_client PUBLIC cpprestsdk::cpprest yaml-cpp fmt)
    else()
        target_link_libraries(apollo_client PUBLIC cpprestsdk::cpprest yaml-cpp)
    endif()
    target_include_directories(apollo_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endif ()

add_subdirectory(test)

#add_subdirectory(service)


