
add_library(soffice_mgr soffice_mgr.cpp)
target_include_directories(soffice_mgr PUBLIC .)
target_compile_features(soffice_mgr PRIVATE cxx_std_23)

target_link_libraries(soffice_mgr PUBLIC Boost::system Boost::filesystem)
