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
#include <string>

#include "doctest/doctest.h"
#include "font_params.h"  // your header

TEST_CASE("font_color default values and assignment") {
  opg::font_color color{};

  // default floats are zero-initialized in C++ aggregate initialization
  CHECK(color.red == 0.0f);
  CHECK(color.green == 0.0f);
  CHECK(color.blue == 0.0f);

  // assign values
  color.red = 0.5f;
  color.green = 0.25f;
  color.blue = 1.0f;

  CHECK(color.red == 0.5f);
  CHECK(color.green == 0.25f);
  CHECK(color.blue == 1.0f);
}

TEST_CASE("font_params default and assignment") {
  opg::font_params params{};

  // default values
  CHECK(params.font_name_.empty());
  CHECK(params.font_size_ == 0.0f);
  CHECK(params.font_color_.red == 0.0f);
  CHECK(params.font_color_.green == 0.0f);
  CHECK(params.font_color_.blue == 0.0f);
  CHECK(params.rotation_ == 0.0f);
  CHECK(params.trasperancy == 0.0f);
  CHECK(params.text_.empty());

  // assign values
  params.font_name_ = "Helvetica";
  params.font_size_ = 12.5f;
  params.font_color_ = {0.1f, 0.2f, 0.3f};
  params.rotation_ = 45.0f;
  params.trasperancy = 0.2f;
  params.text_ = "Hello";

  CHECK(params.font_name_ == "Helvetica");
  CHECK(params.font_size_ == 12.5f);
  CHECK(params.font_color_.red == 0.1f);
  CHECK(params.font_color_.green == 0.2f);
  CHECK(params.font_color_.blue == 0.3f);
  CHECK(params.rotation_ == 45.0f);
  CHECK(params.trasperancy == 0.2f);
  CHECK(params.text_ == "Hello");
}
