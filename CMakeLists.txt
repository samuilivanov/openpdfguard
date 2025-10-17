cmake_minimum_required(VERSION 3.15...4.0)

project(
  openpdfguard
  VERSION 0.1
  DESCRIPTION "A toolkit that converts files to pdf adds watermark and password"
  LANGUAGES CXX)

option(ENABLE_COVERAGE "Enable coverage reporting" OFF)
if(ENABLE_COVERAGE)
  message(STATUS "Building with coverage flags")
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
  endif()
endif()

if(ENABLE_COVERAGE)
  find_program(LCOV lcov)
  find_program(GENHTML genhtml)

  if(LCOV AND GENHTML)
    add_custom_target(coverage
      COMMAND ${LCOV} --directory . --zerocounters
      COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
      COMMAND ${LCOV} --directory . --capture --output-file coverage.info
      COMMAND ${LCOV} --remove coverage.info '/usr/*' --output-file coverage.info
      COMMAND ${GENHTML} coverage.info --output-directory coverage-report
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
      COMMENT "Running tests and generating coverage report"
    )
  else()
    message(WARNING "lcov or genhtml not found! Coverage target will not work.")
  endif()
endif()
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  set(CMAKE_CXX_EXTENSIONS OFF)

  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  include(CTest)

  find_package(Doxygen)
  if(Doxygen_FOUND)
    add_subdirectory(docs)
  else()
    message(STATUS "Doxygen not found, not building docs")
  endif()
endif()

add_subdirectory(src)
add_subdirectory(app)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING)
   AND BUILD_TESTING)
  add_subdirectory(tests)
endif()

find_program(CPPCHECK cppcheck)

if(CPPCHECK)
    # List of source files for cppcheck (could be entire src dir)
    file(GLOB_RECURSE CPP_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB_RECURSE HEADER_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)

    set(CPPCHECK_OPTIONS
        --enable=all
        --language=c++
        --inconclusive
        --force
        --std=c++17
        --inline-suppr
        --verbose
        --suppress=missingIncludeSystem
    )

    add_custom_target(cppcheck
        COMMAND ${CPPCHECK} ${CPPCHECK_OPTIONS}
                -I ${CMAKE_CURRENT_SOURCE_DIR}/src
        -I ${CMAKE_CURRENT_SOURCE_DIR}/include
        -I ${CMAKE_CURRENT_SOURCE_DIR}/build
                ${CPP_FILES} -I ${HEADER_FILES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Running cppcheck..."
        VERBATIM
    )
endif()


if(CLANG_TIDY)
file(GLOB_RECURSE CPP_FILES_CLANG_TIDY
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB_RECURSE HEADER_FILES_CLANG_TIDY
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)


add_custom_target(clang-tidy
    COMMAND ${CLANG_TIDY}
            -p=${CMAKE_BINARY_DIR}
            -checks=${CLANG_TIDY_CHECKS}
            ${CPP_FILES_CLANG_TIDY}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Running clang-tidy on all source files..."
    VERBATIM
)
endif()

# Find Python interpreter
find_package(Python3 COMPONENTS Interpreter REQUIRED)

# Find cpplint script
find_program(CPPLINT cpplint
    HINTS ${Python3_EXECUTABLE_DIR} ENV PATH
)

if(CPPLINT)
    # Reuse the same file lists as cppcheck
    file(GLOB_RECURSE CPP_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    )

    file(GLOB_RECURSE HEADER_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
    )

    # Combine files
    set(CPPLINT_FILES ${CPP_FILES} ${HEADER_FILES})

    # Optional cpplint options
    set(CPPLINT_OPTIONS
        --filter=-build/include_subdir,-build/c++11
        --verbose=2
    )

    add_custom_target(cpplint
        COMMAND ${Python3_EXECUTABLE} ${CPPLINT} ${CPPLINT_OPTIONS} ${CPPLINT_FILES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Running cpplint for C++ style checking..."
        VERBATIM
    )
endif()