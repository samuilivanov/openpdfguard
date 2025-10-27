find_package(Boost REQUIRED COMPONENTS system filesystem)
find_package(Python3 COMPONENTS Interpreter REQUIRED)
find_library(PODOFO_LIB NAMES podofo
  HINTS /usr/lib /usr/lib/x86_64-linux-gnu)

if(NOT PODOFO_LIB)
  message(FATAL_ERROR "PoDoFo not found")
endif()

if(DEFINED ENV{OO_SDK_HOME})
    set(OO_SDK_HOME $ENV{OO_SDK_HOME})
else()
    message(FATAL_ERROR "OO_SDK_HOME not set. Please run the LibreOffice SDK setup first.")
endif()

if(DEFINED ENV{OFFICE_HOME})
    set(OFFICE_HOME $ENV{OFFICE_HOME})
else()
    message(FATAL_ERROR "OFFICE_HOME not set. Please run the LibreOffice SDK setup first.")
endif()

if(DEFINED ENV{OO_SDK_OUT})
    set(OO_SDK_OUT $ENV{OO_SDK_OUT})
else()
    message(FATAL_ERROR "OO_SDK_OUT not set. Please run the LibreOffice SDK setup first.")
endif()

# for #include <osl/process.h>
# Uno headers
find_path(UNO_INCLUDE_DIR
  NAMES cppuhelper/bootstrap.hxx
  HINTS
  /usr/include/libreoffice
  /usr/lib/libreoffice/sdk/include
)

if(NOT UNO_INCLUDE_DIR)
  message(FATAL_ERROR "LibreOffice UNO headers not found")
endif()