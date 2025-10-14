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

#include <memory>

#include "font_params.h"
#include "image_to_pdf.h"
namespace opg {

void pdf_guard::convert_file(std::string_view input, std::string_view output,
                             pdf_opt opt) {
  convert_to_pdf(input, output);
  if (opt.add_watermark_) {
    add_watermark(output, opt.font_params_);
  }
  if (opt.add_encryption_) {
    add_encription(output, opt.user_password_, opt.owner_password_, opt.perms_);
  }
}
void pdf_guard::add_watermark(std::string_view pdf_filename,
                              font_params params) {
  file.load(pdf_filename);
  file.add_text_watermark(params);
  file.save(pdf_filename);
}

void pdf_guard::add_encription(std::string_view pdf_filename,
                               const std::string& userPassword,
                               const std::string& ownerPassword,
                               pdf_permissions protection) {
  file.load(pdf_filename);
  file.add_encryption(userPassword, ownerPassword, protection);
  file.save(pdf_filename);
}
void pdf_guard::convert_to_pdf(std::string_view input,
                               std::string_view output) {
  std::unique_ptr<image_to_pdf> converter = std::make_unique<image_to_pdf>();
  converter->convert(input, output);
}

}  // namespace opg