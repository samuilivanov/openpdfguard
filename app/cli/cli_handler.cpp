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

#include "cli_handler.h"

#include <iostream>

#include "pdf_file.h"
#include "pdf_guard.h"

namespace {
struct perm_map {
  const char *name;
  opg::pdf_permissions value;
};

perm_map permission_table[] = {
    {"print", opg::pdf_permissions::print},
    {"edit", opg::pdf_permissions::edit},
    {"copy", opg::pdf_permissions::copy},
    {"edit_notes", opg::pdf_permissions::edit_notes},
    {"fill_and_sign", opg::pdf_permissions::fill_and_sign},
    {"accessible", opg::pdf_permissions::accessible},
    {"doc_assembly", opg::pdf_permissions::doc_assembly},
    {"high_print", opg::pdf_permissions::high_print}};
}  // namespace

namespace opg::cli {

cli_handler::cli_handler()
    : app_("OpenPdfGuard CLI"),
      watermark_font_("Helvetica"),
      watermark_size_(12),
      watermark_rotation_(45) {}

void cli_handler::setup_global_options() {
  app_.add_option("-i,--input", input_file_, "Path to the input file")
      ->required();
  app_.add_option("-o,--output", output_dir_, "Path to the output directory")
      ->required();
}

void cli_handler::setup_convert_command() {
  CLI::App *convert =
      app_.add_subcommand("convert",
                          "Convert the input file to PDF format and save it in "
                          "the output directory");

  convert->callback([&]() {
    std::cout << "[convert] input: " << input_file_
              << " -> output dir: " << output_dir_ << std::endl;
    opg::pdf_guard guard;
    std::filesystem::path output_file_name = output_dir_;
    output_file_name += input_file_.stem().replace_extension(".pdf");
    guard.convert_to_pdf(input_file_.string(), output_file_name.string());
  });
}

void cli_handler::setup_watermark_command() {
  CLI::App *watermark = app_.add_subcommand(
      "watermark",
      "Apply a watermark. Can be used standalone or chained after 'convert'.");

  watermark->add_option("-t,--text", watermark_text_, "Watermark text")
      ->required();
  watermark->add_option("-f,--font", watermark_font_, "Font name or path")
      ->default_val("Helvetica");
  watermark->add_option("-s,--size", watermark_size_, "Font size")
      ->default_val(12);
  watermark
      ->add_option("-r,--rotation", watermark_rotation_, "Rotation in degrees")
      ->default_val(45);

  watermark->callback([&]() {
    std::cout << "[watermark] text: '" << watermark_text_
              << "', font: " << watermark_font_ << ", size: " << watermark_size_
              << ", rotation: " << watermark_rotation_ << std::endl;
    std::filesystem::path output_file_name = output_dir_;
    output_file_name += input_file_.stem().replace_extension(".pdf");
    opg::pdf_guard guard;
    opg::font_params params = opg::font_params::builder()
                                  .set_text(watermark_text_)
                                  .set_font_name(watermark_font_)
                                  .set_font_size(watermark_size_)
                                  .set_rotation(watermark_rotation_)
                                  .build();
    guard.add_watermark(output_file_name.string(), params);
  });
}

void cli_handler::setup_encrypt_command() {
  CLI::App *encrypt = app_.add_subcommand(
      "encrypt", "Encrypt the PDF file and save it to the output directory");

  encrypt
      ->add_option("-u,--user_password", user_password_,
                   "Password required to open the PDF")
      ->required();
  encrypt
      ->add_option("-o,--owner_password", owner_password_,
                   "Password giving full access to the PDF")
      ->required();

  encrypt
      ->add_option("-p,--permissions", perms_,
                   "Allowed permissions: print, edit, copy, edit_notes, "
                   "fill_and_sign, accessible, doc_assembly, high_print")
      ->check(
          CLI::IsMember({"print", "edit", "copy", "edit_notes", "fill_and_sign",
                         "accessible", "doc_assembly", "high_print"}));
  opg::pdf_permissions perms = opg::pdf_permissions::none;
  std::stringstream ss(perms_);
  std::string token;

  while (std::getline(ss, token, ',')) {
    // remove whitespace
    token.erase(token.begin(),
                std::find_if(token.begin(), token.end(),
                             [](int c) { return !std::isspace(c); }));
    token.erase(std::find_if(token.rbegin(), token.rend(),
                             [](int c) { return !std::isspace(c); })
                    .base(),
                token.end());

    // match to permission
    bool found = false;
    for (auto &p : permission_table) {
      if (token == p.name) {
        perms |= p.value;
        found = true;
        break;
      }
    }
    if (!found) {
      std::cout << "Warning: unknown permission '" << token << "'\n";
    }
  }

  encrypt->callback([&]() {
    std::filesystem::path output_file_name = output_dir_;
    output_file_name += input_file_.stem().replace_extension(".pdf");
    opg::pdf_guard guard;
    guard.add_encryption(output_file_name.string(), user_password_,
                         owner_password_, perms);
  });
}

int cli_handler::run(int argc, char **argv) {
  setup_global_options();
  setup_convert_command();
  setup_watermark_command();
  setup_encrypt_command();
  CLI11_PARSE(app_, argc, argv);
  return 0;
}
}  // namespace opg::cli
