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

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <filesystem>
#include <fstream>

#include "doctest/doctest.h"
#include "pdf_file.h"

using namespace opg;

namespace {
const char* test_pdf_filename = "test.pdf";
const char* output_pdf_filename = "output.pdf";

void create_dummy_pdf(const char* filename) {
  PoDoFo::PdfMemDocument doc;
  PoDoFo::PdfPage* page = doc.CreatePage(
      PoDoFo::PdfPage::CreateStandardPageSize(PoDoFo::ePdfPageSize_A4));
  doc.Write(filename);
}
}  // namespace

TEST_CASE("pdf_file load and save") {
  create_dummy_pdf(test_pdf_filename);

  pdf_file file;

  CHECK_NOTHROW(file.load(test_pdf_filename));

  font_params params;
  params.font_name_ = "Helvetica";
  params.font_size_ = 24.0f;
  params.font_color_ = {1.0f, 0.0f, 0.0f};
  params.rotation = 0.0f;
  params.trasperancy = 0.5f;
  params.text_ = "Test Watermark";

  CHECK_NOTHROW(file.add_text_watermark(params));

  CHECK_NOTHROW(file.save(output_pdf_filename));

  // Check if output file exists
  CHECK(std::filesystem::exists(output_pdf_filename));

  // Cleanup
  std::filesystem::remove(test_pdf_filename);
  std::filesystem::remove(output_pdf_filename);
}

TEST_CASE("pdf_file load invalid file") {
  pdf_file file;
  CHECK_THROWS(file.load("non_existing.pdf"));
}

TEST_CASE("pdf_file save without load") {
  pdf_file file;
  font_params params;
  params.font_name_ = "Arial";
  params.font_size_ = 12.0f;
  params.font_color_ = {0, 0, 0};
  params.rotation = 0;
  params.trasperancy = 1;
  params.text_ = "Hello";

  CHECK_NOTHROW(file.add_text_watermark(params));

  // Saving without loading creates a new empty document in memory
  CHECK_NOTHROW(file.save(output_pdf_filename));
  CHECK(std::filesystem::exists(output_pdf_filename));
  std::filesystem::remove(output_pdf_filename);
}
