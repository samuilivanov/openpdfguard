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

#include <iostream>

#include "file_to_pdf.h"

namespace opg {
class unknown_converter : public file_to_pdf {
 public:
  inline void convert(std::string_view input,
                      [[maybe_unused]] std::string_view output) override {
    std::cerr << "[Warning] Unknown file type, skipping: " << input << "\n";
  }
};
}  // namespace opg
