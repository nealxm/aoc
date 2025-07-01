cmake_minimum_required(VERSION 3.20)
project(aoc2015 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()

include(ProcessorCount)
ProcessorCount(N)
set(CMAKE_BUILD_PARALLEL_LEVEL ${N})

set(flags
    -Wall -Wextra -Wpedantic -Weverything
    -Wno-pre-c23-compat
    -Wno-declaration-after-statement
    -Wno-poison-system-directories
    -Wno-missing-prototypes
    -DDEBUG -g -O3
)

add_library(common STATIC src/common/utils.c)
target_include_directories(common PRIVATE src/common)
target_compile_options(common PRIVATE ${flags})

set(day_dirs "")
set(day_targets "")

foreach(day_num RANGE 1 25)
    if(day_num LESS 10)
        set(day "0${day_num}")
    else()
        set(day "${day_num}")
    endif()

    set(day_dir "src/day${day}")
    set(day_target "day${day}")
    if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${day_dir}")
        continue()
    endif()

    add_library(${day_target} STATIC ${day_dir}/day${day}.c)
    target_include_directories(${day_target} PRIVATE ${day_dir} src/common)
    target_compile_options(${day_target} PRIVATE ${flags})

    list(APPEND day_dirs ${day_dir})
    list(APPEND day_targets ${day_target})

    set(test_target "day${day}_test")
    add_executable(${test_target} ${day_dir}/day${day}_test.c)
    target_include_directories(${test_target} PRIVATE ${day_dir} src/common)
    target_link_libraries(${test_target} PRIVATE ${day_target} common)
    target_compile_options(${test_target} PRIVATE ${flags})

    add_test(NAME "day${day}" COMMAND ${test_target})
    set_tests_properties("day${day}" PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${day_dir}"
    )
endforeach()

add_executable(main main.c)
target_include_directories(main PRIVATE ${day_dirs})
target_link_libraries(main common ${day_targets})
target_compile_options(main PRIVATE ${flags})
