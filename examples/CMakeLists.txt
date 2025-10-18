add_compile_definitions(SAL_UNX)

function(example_binary name)
    add_executable(${name} ${name}.cpp
        ${HEADER_LIST})
    target_include_directories(${name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include /usr/include/libreoffice/ /home/samuil/libreoffice24.2_sdk/include)
    target_compile_features(${name} PRIVATE cxx_std_23)
    target_link_directories(${name} PRIVATE /usr/lib/libreoffice/sdk/lib/ /usr/lib/libreoffice/program/)
    target_link_libraries(${name} PRIVATE podofo pdfguard uno_cppuhelpergcc3 uno_sal uno_cppu uno_purpenvhelpergcc3 uno_salhelpergcc3 reglo)

endfunction()

example_binary(convert_pdf)
example_binary(full_pipeline)
example_binary(watermark_pdf)
