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

#include "pdf_file.h"

#include <podofo/base/PdfEncrypt.h>

#include <string>
#include <string_view>
namespace opg {

// TODO(samuil): add the option to open with password
bool pdf_file::load(std::string_view filename) {
  default_filename_ = filename;
  try {
    document_.Load(filename.data(), true);
  } catch (const PoDoFo::PdfError &e) {  // catch by reference
    std::cerr << "PoDoFo error: " << e.GetError() << " (" << e.what() << ")"
              << std::endl;
    return false;
  } catch (const std::exception &e) {
    std::cerr << "Standard exception: " << e.what() << std::endl;
    return false;
  } catch (...) {
    std::cerr << "Unknown exception occurred" << std::endl;
    return false;
  }
  return true;
}

void pdf_file::add_text_watermark(const font_params &params) {
  for (int i = 0; i < document_.GetPageCount(); ++i) {
    PoDoFo::PdfPage *page = document_.GetPage(i);
    PoDoFo::PdfPainter painter;
    painter.SetPage(page);

    PoDoFo::PdfFont *font = document_.CreateFont(params.font_name_.data());
    font->SetFontSize(64.0);
    painter.SetFont(font);

    painter.SetColor(params.font_color_.red, params.font_color_.green,
                     params.font_color_.blue);

    const PoDoFo::PdfRect &rect = page->GetPageSize();
    double x = rect.GetWidth() / 4.0;
    double y = rect.GetHeight() / 2.0;

    painter.Save();
    double angle_rad = params.rotation_ * M_PI / 180.0;
    double cos_a = cos(angle_rad);
    double sin_a = sin(angle_rad);

    // affine transformation matrix: [ a b c d e f ]
    // | a c e |
    // | b d f |
    // | 0 0 1 |
    // rotate around page center
    painter.SetTransformationMatrix(cos_a, sin_a, -sin_a, cos_a, x, y);
    // painter.SetTransformationMatrix(1, 0, 0, 1, x, y);
    // painter.Rotate(45.0);

    PoDoFo::PdfExtGState gs(&document_.GetObjects());
    gs.SetFillOpacity(params.trasperancy);
    gs.SetStrokeOpacity(params.trasperancy);
    painter.SetExtGState(&gs);

    painter.DrawText(0, 0, params.text_);
    painter.Restore();

    painter.FinishPage();
  }
}
void pdf_file::save(std::string_view filename) {
  document_.Write(filename.data());
}

bool pdf_file::save() {
  if (default_filename_->empty()) {
    return false;
  }

  try {
    document_.WriteUpdate(default_filename_.value().data());
  } catch (const PoDoFo::PdfError &e) {  // catch by reference
    std::cerr << "PoDoFo error: " << e.GetError() << " (" << e.what() << ")"
              << std::endl;
    return false;
  } catch (const std::exception &e) {
    std::cerr << "Standard exception: " << e.what() << std::endl;
    return false;
  } catch (...) {
    std::cerr << "Unknown exception occurred" << std::endl;
    return false;
  }
  return true;
}

void pdf_file::add_encryption(const std::string &userPassword,
                              const std::string &ownerPassword,
                              pdf_permissions protection) {
  int podofo_perms = to_podofo_permissions(protection);
  try {
    document_.SetEncrypted(userPassword, ownerPassword, podofo_perms,
                           PoDoFo::PdfEncrypt::ePdfEncryptAlgorithm_AESV3R6,
                           PoDoFo::PdfEncrypt::ePdfKeyLength_256);
  } catch (const PoDoFo::PdfError &e) {  // catch by reference
    std::cerr << "PoDoFo error: " << e.GetError() << " (" << e.what() << ")"
              << std::endl;
    e.PrintErrorMsg();
  } catch (const std::exception &e) {
    std::cerr << "Standard exception: " << e.what() << std::endl;
  } catch (...) {
    std::cerr << "Unknown exception occurred" << std::endl;
  }
}
}  // namespace opg
