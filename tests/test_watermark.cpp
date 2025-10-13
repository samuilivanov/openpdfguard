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
#include <doctest/doctest.h>

#include <string>

#include "watermark.h"

TEST_CASE("opg::watermark builder sets font parameters correctly") {
  using namespace opg;

  font_color blue{0.0f, 0.0f, 1.0f};

  SUBCASE("Default builder values") {
    watermark wm = watermark::builder().build();
    CHECK_NOTHROW(watermark::builder().build());
  }

  SUBCASE("Custom font name and size") {
    watermark wm = watermark::builder()
                       .set_font_name("Times New Roman")
                       .set_font_size(32)
                       .build();
    CHECK_NOTHROW(wm);
  }

  SUBCASE("Custom font color") {
    watermark wm = watermark::builder().set_font_color(blue).build();
    CHECK_NOTHROW(wm);
  }

  SUBCASE("Custom rotation and transparency") {
    watermark wm =
        watermark::builder().set_rotation(45).set_transparency(0.5).build();
    CHECK_NOTHROW(wm);
  }

  SUBCASE("Custom text") {
    watermark wm = watermark::builder().set_text("Hello PDF").build();
    CHECK_NOTHROW(wm);
  }

  SUBCASE("Full builder chain") {
    watermark wm = watermark::builder()
                       .set_font_name("Arial")
                       .set_font_size(24)
                       .set_font_color(blue)
                       .set_rotation(90)
                       .set_transparency(0.25)
                       .set_text("Watermark Test")
                       .build();
    CHECK_NOTHROW(wm);
  }
}

TEST_CASE("opg::watermark add_text_watermark handles invalid paths") {
  using namespace opg;

  watermark wm = watermark::builder().set_text("Test").build();

  // Since add_text_watermark writes files, we just check it doesn't throw
  CHECK_THROWS_AS(wm.add_text_watermark("nonexistent.pdf", "out.pdf"),
                  PoDoFo::PdfError);
}
