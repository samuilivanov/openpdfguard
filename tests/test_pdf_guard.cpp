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

#include "font_params.h"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include "pdf_file.h"
#include "pdf_guard.h"

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

namespace opg {
TEST_CASE("pdf_guard can convert, watermark, and encrypt a PDF") {
  create_dummy_pdf(test_pdf_filename);

  pdf_guard guard;

  font_params params =
      font_params::builder().set_text("UNIT TEST").set_font_size(14).build();
  pdf_permissions perms = pdf_permissions::print;
  pdf_opt opt(/*add_watermark=*/true,
              /*add_encryption=*/true,
              /*user=*/"userpass",
              /*owner=*/"ownerpass",
              /*permissions=*/perms, params);

  REQUIRE_NOTHROW(
      guard.convert_file(test_pdf_filename, output_pdf_filename, opt));

  pdf_file result;
  // NO pass passed
  CHECK_FALSE(result.load(output_pdf_filename));
}
}  // namespace opg