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

#include "pdf_guard.h"

#include "watermark.h"

namespace opg {

void pdf_guard::set_output(std::string_view path) { path_ = path; }

void pdf_guard::convert_to_pdf(std::string_view filename) {
  //  detect file type
  // get converter
  // convert to pdf
  // write to output
}
void pdf_guard::add_watermark() {
  // watermark_.add_text_watermark(const std::string &input_pdf, const std::string &output_pdf, const std::string &text)
}
void pdf_guard::set_watermark(const watermark& mark) { watermark_ = mark; }
void pdf_guard::add_password() {}
}  // namespace opg