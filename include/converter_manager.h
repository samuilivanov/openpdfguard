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

#include <string>
#include <unordered_map>

#include "file_to_pdf.h"
#include "image_to_pdf.h"
#include "ms_to_pdf.h"
#include "pdf_to_pdf.h"
#include "unknown_converter.h"

namespace opg {
class converter_manager {
 private:
  pdf_to_pdf pdf_converter_;
  ms_to_pdf doc_converter_;
  image_to_pdf image_converter_;
  unknown_converter unknown_converter_;

  std::unordered_map<std::string, file_to_pdf *> converters_;

 public:
  converter_manager();

  file_to_pdf *get_converter(const std::string &mime);
};

}  // namespace opg
