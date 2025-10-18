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
#include <podofo/podofo.h>

#include <optional>
#include <string>
#include <string_view>

#include "font_params.h"

namespace opg {

enum class pdf_permissions : uint32_t {
  none = 0x00000000,
  print = 0x00000001,
  edit = 0x00000002,
  copy = 0x00000004,
  edit_notes = 0x00000008,
  fill_and_sign = 0x00000010,
  accessible = 0x00000020,
  doc_assembly = 0x00000040,
  high_print = 0x00000080
};

inline pdf_permissions operator|(pdf_permissions lhs, pdf_permissions rhs) {
  return static_cast<pdf_permissions>(
      static_cast<std::underlying_type_t<pdf_permissions>>(lhs) |
      static_cast<std::underlying_type_t<pdf_permissions>>(rhs));
}

inline pdf_permissions& operator|=(pdf_permissions& lhs, pdf_permissions rhs) {
  lhs = lhs | rhs;
  return lhs;
}

inline pdf_permissions operator&(pdf_permissions lhs, pdf_permissions rhs) {
  return static_cast<pdf_permissions>(
      static_cast<std::underlying_type_t<pdf_permissions>>(lhs) &
      static_cast<std::underlying_type_t<pdf_permissions>>(rhs));
}

inline bool has_flag(pdf_permissions value, pdf_permissions flag) {
  return (static_cast<std::underlying_type_t<pdf_permissions>>(value) &
          static_cast<std::underlying_type_t<pdf_permissions>>(flag)) != 0;
}

// Translator from your permissions to PoDoFo EPdfPermissions
inline int to_podofo_permissions(pdf_permissions perms) {
  int result = 0;

  if (has_flag(perms, pdf_permissions::print)) {
    result |= PoDoFo::PdfEncrypt::ePdfPermissions_Print;
  }
  if (has_flag(perms, pdf_permissions::edit)) {
    result |= PoDoFo::PdfEncrypt::ePdfPermissions_Edit;
  }
  if (has_flag(perms, pdf_permissions::copy)) {
    result |= PoDoFo::PdfEncrypt::ePdfPermissions_Copy;
  }
  if (has_flag(perms, pdf_permissions::edit_notes)) {
    result |= PoDoFo::PdfEncrypt::ePdfPermissions_EditNotes;
  }
  if (has_flag(perms, pdf_permissions::fill_and_sign)) {
    result |= PoDoFo::PdfEncrypt::ePdfPermissions_FillAndSign;
  }
  if (has_flag(perms, pdf_permissions::accessible)) {
    result |= PoDoFo::PdfEncrypt::ePdfPermissions_Accessible;
  }
  if (has_flag(perms, pdf_permissions::doc_assembly)) {
    result |= PoDoFo::PdfEncrypt::ePdfPermissions_DocAssembly;
  }
  if (has_flag(perms, pdf_permissions::high_print)) {
    result |= PoDoFo::PdfEncrypt::ePdfPermissions_HighPrint;
  }

  return result;
}

class pdf_file {
 private:
  PoDoFo::PdfMemDocument document_;
  std::optional<std::string> default_filename_;  // optional

 public:
  bool load(std::string_view filename);
  void add_text_watermark(const font_params& params);
  bool save();
  void save(std::string_view filename);
  // TODO(samuil):
  // add_image_watermark();
  void add_encryption(const std::string& userPassword,
                      const std::string& ownerPassword,
                      pdf_permissions protection);
};
}  // namespace opg
