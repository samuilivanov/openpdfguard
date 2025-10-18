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

#include <iostream>

#include "font_params.h"
#include "pdf_guard.h"

int main() {
  opg::pdf_guard guard;
  opg::font_params params = opg::font_params::builder()
                                .set_text("SAMPLE WATERMARK")
                                .set_font_size(12)
                                .build();

  opg::pdf_opt opt(true, true, "user", "owner", {}, params);
  guard.convert_file("input.docx", "output.pdf", opt);

  std::cout << "Full pipeline complete!\n";
}
