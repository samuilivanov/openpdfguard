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

#include "watermark.h"

namespace opg {
void watermark::add_text_watermark(const std::string &input_pdf,
                                   const std::string &output_pdf) {
  PoDoFo::PdfMemDocument document;
  document.Load(input_pdf.c_str());

  for (int i = 0; i < document.GetPageCount(); ++i) {
    PoDoFo::PdfPage *page = document.GetPage(i);
    PoDoFo::PdfPainter painter;
    painter.SetPage(page);

    PoDoFo::PdfFont *font = document.CreateFont(font_params_.font_name_.data());
    font->SetFontSize(64.0);
    painter.SetFont(font);

    // PdfExtGState *state = document.CreateExtGState();
    // state->SetFillOpacity(0.2);
    // painter.SetExtGState(state);
    painter.SetColor(font_params_.font_color_.red,
                     font_params_.font_color_.green,
                     font_params_.font_color_.blue);

    const PoDoFo::PdfRect &rect = page->GetPageSize();
    double x = rect.GetWidth() / 4.0;
    double y = rect.GetHeight() / 2.0;

    painter.Save();
    double angle_rad = font_params_.rotation * M_PI / 180.0;
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

    PoDoFo::PdfExtGState gs(&document.GetObjects());
    gs.SetFillOpacity(font_params_.trasperancy);
    gs.SetStrokeOpacity(font_params_.trasperancy);
    painter.SetExtGState(&gs);

    painter.DrawText(0, 0, font_params_.text_);
    painter.Restore();

    painter.FinishPage();
  }

  document.Write(output_pdf.c_str());
}
}  // namespace opg