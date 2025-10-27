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

#include <CLI/CLI.hpp>
#include <filesystem>
#include <string>
namespace opg::cli {

class cli_handler {
 public:
  cli_handler();
  int run(int argc, char **argv);

 private:
  CLI::App app_;
  std::filesystem::path input_file_;
  std::filesystem::path output_dir_;

  // watermark options
  std::string watermark_text_;
  std::string watermark_font_;
  float watermark_size_;
  float watermark_rotation_;

  // encrypt options
  std::string user_password_;
  std::string owner_password_;
  std::string perms_;

  void setup_global_options();
  void setup_convert_command();
  void setup_watermark_command();
  void setup_encrypt_command();
};
}  // namespace opg::cli