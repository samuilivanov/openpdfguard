file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${fika_SOURCE_DIR}/src/supervisor/include/*.h")


add_executable(openpdfguard main.cpp
    ${HEADER_LIST})
target_include_directories(openpdfguard PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_compile_features(openpdfguard PRIVATE cxx_std_23)

target_link_libraries(openpdfguard PRIVATE podofo pdfguard)

install(TARGETS openpdfguard
    RUNTIME DESTINATION ${FIKA_BINDIR}
)
