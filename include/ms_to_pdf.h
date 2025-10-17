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
 *
 * This file uses interfaces from the LibreOffice UNO API,
 * licensed under the Mozilla Public License v2.0.
 * See: https://www.mozilla.org/MPL/2.0/
 *
 */

#pragma once

#include "file_to_pdf.h"

namespace opg {
class ms_to_pdf : public file_to_pdf {
 public:
  void convert(std::string_view input, std::string_view output) override;
};
}  // namespace opg
