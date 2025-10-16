file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${fika_SOURCE_DIR}/src/supervisor/include/*.h")

add_compile_definitions(SAL_UNX)
add_executable(openpdfguard main.cpp
    ${HEADER_LIST})
target_include_directories(openpdfguard PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include /usr/include/libreoffice/ /home/samuil/libreoffice24.2_sdk/include)
target_compile_features(openpdfguard PRIVATE cxx_std_23)
target_link_directories(openpdfguard PRIVATE /usr/lib/libreoffice/sdk/lib/  /usr/lib/libreoffice/program/)
target_link_libraries(openpdfguard PRIVATE podofo pdfguard uno_cppuhelpergcc3 uno_sal uno_cppu uno_purpenvhelpergcc3 uno_salhelpergcc3 reglo)

install(TARGETS openpdfguard
    RUNTIME DESTINATION ${FIKA_BINDIR}
)
