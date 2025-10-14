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

#include "image_to_pdf.h"

#include <podofo/podofo.h>
namespace opg {

void image_to_pdf::convert(std::string_view input, std::string_view output) {
  PoDoFo::PdfStreamedDocument doc(output.data());

  PoDoFo::PdfImage image(&doc);
  image.LoadFromFile(input.data());

  // use image dimensions for page size
  const double img_w = static_cast<double>(image.GetWidth());
  const double img_h = static_cast<double>(image.GetHeight());

  PoDoFo::PdfPage* page = doc.CreatePage(PoDoFo::PdfRect(0.0, 0.0, img_w, img_h));

  PoDoFo::PdfPainter painter;
  painter.SetPage(page);
  painter.DrawImage(0.0, 0.0, &image, 1, 1);
  painter.FinishPage();

  doc.Close();
}
}  // namespace opg
