# ---------------- cppcheck ----------------
find_program(CPPCHECK cppcheck)
if(CPPCHECK)
  file(GLOB_RECURSE CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
  file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
  set(CPPCHECK_OPTIONS
    --enable=all --language=c++ --inconclusive --force
    --std=c++17 --inline-suppr --verbose --suppress=missingIncludeSystem)
  add_custom_target(cppcheck
    COMMAND ${CPPCHECK} ${CPPCHECK_OPTIONS}
    -I ${CMAKE_CURRENT_SOURCE_DIR}/src
    -I ${CMAKE_CURRENT_SOURCE_DIR}/include
    -I ${CMAKE_CURRENT_SOURCE_DIR}/build
    ${CPP_FILES} -I ${HEADER_FILES}
    COMMENT "Running cppcheck..."
  )
endif()

# ---------------- clang-tidy ----------------
find_program(CLANG_TIDY clang-tidy)


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

# ---------------- cpplint ----------------
find_program(CPPLINT cpplint HINTS ${Python3_EXECUTABLE_DIR} ENV PATH)
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
