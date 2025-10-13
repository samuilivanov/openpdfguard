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
#include <filesystem>
#include <string_view>

#include "watermark.h"

namespace opg {
class pdf_guard {
 private:
  std::filesystem::path path_;
  watermark watermark_;

 public:
  void set_output(std::string_view path);
  void convert_to_pdf(std::string_view filename);
  void set_watermark(const watermark& mark);
  void add_watermark();
  void add_password();
};
// detect file type
// list of converters
}  // namespace opg