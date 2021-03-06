cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 11)
project(music-visualizer)

# This tells the compiler to not aggressively optimize and
# to include debugging information so that the debugger
# can properly read what's going on.
set(CMAKE_BUILD_TYPE Debug)

# Let's ensure -std=c++xx instead of -std=g++xx
set(CMAKE_CXX_EXTENSIONS OFF)

# Let's nicely support folders in IDE's
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Warning flags
if(MSVC)
    # warning level 3 and all warnings as errors
    add_compile_options(/W3 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wpedantic -Werror)
endif()

# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)

# FetchContent_MakeAvailable was not added until CMake 3.14
if(${CMAKE_VERSION} VERSION_LESS 3.14)
    include(cmake/add_FetchContent_MakeAvailable.cmake)
endif()

FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.x
)

set(Boost_USE_STATIS_LIBS OFF)
set(Boost_USE MUTLTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(BOOST_ROOT /local/boost_1_74_0)
set(BOOST_INCLUDEDIR /local/boost_1_74_0)
set(BOOST_LIBRARYDIR /local/boost_1_74_0/lib64-msvc-14.0)
find_package(Boost REQUIRED)

if (Boost_FOUND)
    include_directories(${BOOST_INCLUDEDIR})
    add_library(boost INTERFACE)
endif ()

# Adds Catch2 testing library
FetchContent_GetProperties(catch2)
if(NOT catch2_POPULATED)
    FetchContent_Populate(catch2)
    add_library(catch2 INTERFACE)
    target_include_directories(catch2 INTERFACE ${catch2_SOURCE_DIR}/single_include)
endif()

get_filename_component(CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../" ABSOLUTE)
get_filename_component(APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/" ABSOLUTE)

include("${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake")

# add source files here i.e. "list(APPEND CORE_SOURCE_FILES src/core/classifier.cc)"

list(APPEND SOURCE_FILES    ${CORE_SOURCE_FILES}
        # add some files here i.e. "src/visualizer/naive_bayes_app.cc"
        src/visualizer/music_visualizer_app.cc
        src/core/node.cc
        src/core/container.cc
        src/core/connector.cc
        src/music_player/music_player.cc
        src/controls/color_picker.cc
        src/controls/color_bar.cc
        src/controls/color_segment.cc
        src/controls/color_palette.cc
        )

list(APPEND TEST_FILES tests/music_visualizer_test.cc# add test files here i.e. "tests/test_classifier.cc"
        )

#add_executable(music-visualizer apps/cinder_app_main.cc ${CORE_SOURCE_FILES} ${Boost_LIBRARIES})
        # add executable here i.e. "train-model apps/train_model_main.cc ${CORE_SOURCE_FILES})"
#target_include_directories(train-model PRIVATE include)

ci_make_app(
        APP_NAME        music-visualizer
        CINDER_PATH     ${CINDER_PATH}
        SOURCES         apps/cinder_app_main.cc ${SOURCE_FILES}
        INCLUDES        include
        LIBRARIES       boost
)

ci_make_app(
        APP_NAME        music-visualizer-test
        CINDER_PATH     ${CINDER_PATH}
        SOURCES         tests/test_main.cc ${SOURCE_FILES} ${TEST_FILES}
        INCLUDES        include
        LIBRARIES       catch2
)

if(MSVC)
    set_property(TARGET music-visualizer-test APPEND_STRING PROPERTY LINK_FLAGS " /SUBSYSTEM:CONSOLE")
endif()