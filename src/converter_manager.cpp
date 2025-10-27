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

#include "converter_manager.h"
namespace {

std::string normalize_mime(const std::string &mime) {
  if (mime == "application/x-pdf") return "application/pdf";
  if (mime == "application/octet-stream") return "application/pdf";
  if (mime == "image/x-tiff") return "image/tiff";
  if (mime.find("text/") == 0) return "text/plain";

  return mime;
}
}  // namespace

namespace opg {

converter_manager::converter_manager() {
  // Create one instance per supported type
  converters_["application/pdf"] = &pdf_converter_;
  converters_["application/msword"] = &doc_converter_;
  converters_["application/doc"] = &doc_converter_;
  converters_["application/ms-doc"] = &doc_converter_;
  converters_
      ["application/"
       "vnd.openxmlformats-officedocument.wordprocessingml.document"] =
          &doc_converter_;
  converters_["application/vnd.oasis.opendocument.text"] = &doc_converter_;
  converters_["application/excel"] = &doc_converter_;
  converters_["application/vnd.ms-excel"] = &doc_converter_;
  converters_["application/x-excel"] = &doc_converter_;
  converters_["application/x-msexcel"] = &doc_converter_;
  converters_
      ["application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"] =
          &doc_converter_;
  converters_["application/mspowerpoint"] = &doc_converter_;
  converters_["application/powerpoint"] = &doc_converter_;
  converters_["application/vnd.ms-powerpoint"] = &doc_converter_;
  converters_["application/x-mspowerpoint"] = &doc_converter_;
  converters_
      ["application/"
       "vnd.openxmlformats-officedocument.presentationml.presentation"] =
          &doc_converter_;
  converters_["application/vnd.oasis.opendocument.spreadsheet"] =
      &doc_converter_;
  converters_["application/vnd.oasis.opendocument.presentation"] =
      &doc_converter_;
  converters_["application/rtf"] = &doc_converter_;
  converters_["text/plain"] = &doc_converter_;
  converters_["image/jpeg"] = &image_converter_;
  converters_["image/pjpeg"] = &image_converter_;
  converters_["image/png"] = &image_converter_;
  converters_["image/gif"] = &image_converter_;
  converters_["image/tiff"] = &image_converter_;
}

file_to_pdf *converter_manager::get_converter(const std::string &mime) {
  std::string canonical = normalize_mime(mime);
  auto it = converters_.find(canonical);
  if (it != converters_.end()) return it->second;
  return &unknown_converter_;
}
}  // namespace opg
