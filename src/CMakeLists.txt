# file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${openpdfguard_SOURCE_DIR}/include/*.h")
# message(${HEADER_LIST})
add_compile_definitions(SAL_UNX)

add_library(pdfguard
    pdf_guard.cpp
    pdf_file.cpp
    image_to_pdf.cpp
    ms_to_pdf.cpp
    pdf_to_pdf.cpp
    detect_file.cpp
    converter_manager.cpp)

target_include_directories(pdfguard PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include)

target_include_directories(pdfguard PUBLIC
    SYSTEM
    /usr/include/libreoffice/
    /home/samuil/libreoffice24.2_sdk/include)
target_link_directories(pdfguard PUBLIC /usr/lib/libreoffice/sdk/lib/ /usr/lib/libreoffice/program/)
target_compile_features(pdfguard PRIVATE cxx_std_23)

target_link_libraries(pdfguard PRIVATE
    podofo
    uno_cppuhelpergcc3
    uno_sal
    uno_cppu
    uno_purpenvhelpergcc3
    uno_salhelpergcc3
    reglo magic
    soffice_mgr
)

install(TARGETS pdfguard
    RUNTIME DESTINATION ${FIKA_BINDIR}
)
