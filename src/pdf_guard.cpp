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

#include "detect_file.h"
#include "font_params.h"
#include "image_to_pdf.h"
#include "ms_to_pdf.h"
#include "pdf_file.h"
#include "pdf_to_pdf.h"
#include "soffice/soffice_mgr.h"

namespace opg {

void initialize() { soffice::soffice_mgr::instance().start(); }
void shutdown() { soffice::soffice_mgr::instance().shutdown(); }

// TODO(samuil): this needs to be as a config file
std::unordered_map<std::string, std::shared_ptr<file_to_pdf>>
load_pdf_converters() {
  std::unordered_map<std::string, std::shared_ptr<file_to_pdf>> pdf_converters;

  std::shared_ptr<file_to_pdf> pdf = std::make_shared<pdf_to_pdf>();
  std::shared_ptr<file_to_pdf> doc = std::make_shared<ms_to_pdf>();
  std::shared_ptr<file_to_pdf> img = std::make_shared<image_to_pdf>();

  // all supported aliases
  pdf_converters["application/pdf"] = pdf;
  pdf_converters["application/msword"] = doc;
  pdf_converters["application/vnd.oasis.opendocument.text"] = doc;
  pdf_converters["image/jpeg"] = img;

  return pdf_converters;  // return by value
}
pdf_guard::pdf_guard() : pdf_converters(load_pdf_converters()) {}

void pdf_guard::convert_file(std::string_view input, std::string_view output,
                             const pdf_opt& opt) {
  convert_to_pdf(input, output);
  pdf_file file;
  if (file.load(output)) {
    if (opt.add_watermark_) {
      file.add_text_watermark(opt.font_params_);
    }
    if (opt.add_encryption_) {
      file.add_encryption(opt.user_password_, opt.owner_password_, opt.perms_);
    }
    file.save();
  }
}

void pdf_guard::add_watermark(std::string_view pdf_filename,
                              const font_params& params) {
  pdf_file file;
  if (file.load(pdf_filename)) {
    file.add_text_watermark(params);
    file.save();
  }
}

void pdf_guard::add_encryption(std::string_view pdf_filename,
                               const std::string& userPassword,
                               const std::string& ownerPassword,
                               pdf_permissions protection) {
  pdf_file file;

  if (file.load(pdf_filename)) {
    file.add_encryption(userPassword, ownerPassword, protection);
    file.save();
  }
}

void pdf_guard::convert_to_pdf(std::string_view input,
                               std::string_view output) {
  const std::string mime = get_mime_type(input.data());
  auto it = pdf_converters.find(mime);
  if (it == pdf_converters.end()) {
    throw std::runtime_error("Unsupported file type: " + mime);
  }
  it->second->convert(input, output);
}

}  // namespace opg
