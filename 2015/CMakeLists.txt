cmake_minimum_required(VERSION 4.0.0)
if(APPLE)
    set(CMAKE_C_COMPILER "/opt/homebrew/opt/llvm/bin/clang")
endif()
project(aoc2015 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)
enable_testing()

include(ProcessorCount)
ProcessorCount(N)
set(CMAKE_BUILD_PARALLEL_LEVEL ${N})
set(CTEST_PARALLEL_LEVEL ${N})
set_property(GLOBAL PROPERTY JOB_POOLS default=${N})
set(CMAKE_JOB_POOL_COMPILE default)
set(CMAKE_JOB_POOL_LINK default)

set(flags
    -Wall -Wextra -Wpedantic -Weverything
    -Wno-pre-c23-compat
    -Wno-declaration-after-statement
    -Wno-poison-system-directories
    -Wno-unsafe-buffer-usage
    -DDEBUG -g -O3
)

set(utils_dir "src/common/utils")
add_library(utils OBJECT
    ${utils_dir}/io.c
    ${utils_dir}/math.c
    ${utils_dir}/mem.c
)
target_include_directories(utils PUBLIC ${utils_dir})
target_compile_options(utils PRIVATE ${flags})

set(testing_dir "src/common/testing")
add_library(testing OBJECT ${testing_dir}/testing.c)
target_include_directories(testing PUBLIC ${testing_dir})
target_compile_options(testing PRIVATE ${flags})

set(day_targets "")
set(test_targets "")

foreach(day_num RANGE 1 25)
    if(day_num LESS 10)
        set(day "0${day_num}")
    else()
        set(day "${day_num}")
    endif()

    set(day_target "day${day}")
    set(test_target "${day_target}_test")
    set(day_dir "src/${day_target}")
    if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${day_dir}")
        continue()
    endif()
    list(APPEND day_targets ${day_target})
    list(APPEND test_targets ${test_target})

    add_library(${day_target} OBJECT ${day_dir}/${day_target}.c)
    target_include_directories(${day_target} PUBLIC ${day_dir})
    if(TARGET day04)
        find_package(OpenSSL REQUIRED)
        target_link_libraries(${day_target} PRIVATE OpenSSL::Crypto)
    endif()
    target_link_libraries(${day_target} PRIVATE utils)
    target_compile_options(${day_target} PRIVATE ${flags})

    add_library(${test_target} OBJECT ${day_dir}/${test_target}.c)
    target_link_libraries(${test_target} PRIVATE
        utils
        testing
        ${day_target}
    )
    target_compile_options(${test_target} PRIVATE ${flags})

    file(READ
        "${CMAKE_CURRENT_SOURCE_DIR}/${day_dir}/${test_target}.c" file_str)
    string(REGEX MATCHALL
        "d[0-9][0-9]_p[0-9]_(e[0-9][0-9]|i)" matches ${file_str})
    foreach(match ${matches})
        add_test(NAME ${match}
            COMMAND test_runner ${day_target} ${match}
            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${day_dir}"
        )
    endforeach()
endforeach()

add_executable(test_runner ${testing_dir}/runner.c)
target_link_libraries(test_runner PRIVATE
    utils
    testing
    ${day_targets}
    ${test_targets}
)
target_compile_options(test_runner PRIVATE ${flags})

add_executable(main main.c)
target_link_libraries(main PRIVATE utils ${day_targets})
target_compile_options(main PRIVATE ${flags})
