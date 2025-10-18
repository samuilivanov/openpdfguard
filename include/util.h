
#pragma once

#include <podofo/podofo.h>

#include <cstdlib>
#include <filesystem>
#include <random>
#include <string>

namespace opg::util {

inline std::string generate_tmp_filename(
    const std::string& prefix = "pdf_test_", const std::string& ext = ".pdf") {
  // Generate random alphanumeric string
  static std::mt19937 rng{std::random_device{}()};
  static const char alphanum[] =
      "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  std::uniform_int_distribution<> dist(0, sizeof(alphanum) - 2);

  std::string rand_str;
  for (int i = 0; i < 8; ++i) rand_str += alphanum[dist(rng)];

  // Build /tmp/filename
  std::filesystem::path tmp = std::filesystem::temp_directory_path();
  tmp /= prefix + rand_str + ext;
  return tmp.string();
}

inline std::string create_dummy_pdf() {
  std::string filename = generate_tmp_filename();

  PoDoFo::PdfMemDocument doc;
  PoDoFo::PdfPage* page = doc.CreatePage(
      PoDoFo::PdfPage::CreateStandardPageSize(PoDoFo::ePdfPageSize_A4));
  doc.Write(filename.c_str());

  return filename;
}
}  // namespace opg::util