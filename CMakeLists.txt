cmake_minimum_required(VERSION 3.15...4.0)

project(
  openpdfguard
  VERSION 0.1
  DESCRIPTION "A toolkit that converts files to PDF, adds watermark and password"
  LANGUAGES CXX
)

# --- Build options ---
option(ENABLE_COVERAGE "Enable coverage reporting" OFF)
option(MODERN_CMAKE_BUILD_TESTING "Enable tests in modern cmake" ON)

# --- Include cmake modules ---
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(CompilerWarnings)
include(CodeChecks)
include(Coverage)
include(Docs)
include(Dependencies)

# --- Project configuration ---
set(CMAKE_CXX_EXTENSIONS OFF)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 23)

# --- Subdirectories ---
add_subdirectory(src)
add_subdirectory(src/soffice)
add_subdirectory(app)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()
