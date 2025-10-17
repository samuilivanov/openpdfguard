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

#include "detect_file.h"

#include <magic.h>

#include <stdexcept>

namespace opg {

std::string get_mime_type(const std::string& filename) {
  magic_t magic =
      magic_open(MAGIC_MIME_TYPE);  // Open magic with MIME type option
  if (magic == nullptr) {
    throw std::runtime_error("Failed to initialize libmagic");
  }

  if (magic_load(magic, nullptr) == -1) {
    magic_close(magic);
    throw std::runtime_error("Failed to load magic database");
  }

  const char* mime_type = magic_file(magic, filename.c_str());
  if (mime_type == nullptr) {
    magic_close(magic);
    throw std::runtime_error("Failed to determine MIME type");
  }

  std::string mime_str(mime_type);
  magic_close(magic);
  return mime_str;
}
}  // namespace opg
