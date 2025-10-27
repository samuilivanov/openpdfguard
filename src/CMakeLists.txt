# --- Preprocessor definitions ---
add_compile_definitions(SAL_UNX)

# --- Sources ---
set(PDFGUARD_SOURCES
    pdf_guard.cpp
    pdf_file.cpp
    image_to_pdf.cpp
    ms_to_pdf.cpp
    pdf_to_pdf.cpp
    detect_file.cpp
    converter_manager.cpp
)

# --- Library target ---
add_library(pdfguard ${PDFGUARD_SOURCES})

# --- Include directories ---
target_include_directories(pdfguard
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    SYSTEM
    ${UNO_INCLUDE_DIR}
    ${OO_SDK_OUT}/include
)

# --- Compiler standard ---
target_compile_features(pdfguard PUBLIC cxx_std_23)

target_link_directories(pdfguard PUBLIC ${OO_SDK_HOME}/lib ${OFFICE_HOME}/program)

# --- Find/link libraries ---
target_link_libraries(pdfguard
    PRIVATE
    podofo
    uno_cppuhelpergcc3
    uno_sal
    uno_cppu
    uno_purpenvhelpergcc3
    uno_salhelpergcc3
    reglo
    magic
    soffice_mgr
)

install(TARGETS pdfguard
    RUNTIME DESTINATION ${FIKA_BINDIR}
)
