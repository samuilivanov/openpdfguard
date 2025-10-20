/*
 * This file is part of openpdfguard.
 * Copyright (C) 2025 Samuil Ivanov
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; If not, see <http://www.gnu.org/licenses/>.
 */

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
