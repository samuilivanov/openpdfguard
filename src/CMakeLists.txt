# file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${openpdfguard_SOURCE_DIR}/include/*.h")
# message(${HEADER_LIST})

add_library(pdfguard pdf_guard.cpp pdf_file.cpp image_to_pdf.cpp)
target_include_directories(pdfguard PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_compile_features(pdfguard PRIVATE cxx_std_23)

target_link_libraries(pdfguard PRIVATE)

install(TARGETS pdfguard
    RUNTIME DESTINATION ${FIKA_BINDIR}
)
