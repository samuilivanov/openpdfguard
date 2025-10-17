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

#include <algorithm>
#include <filesystem>

#include "font_params.h"
#include "pdf_file.h"
#include "pdf_guard.h"

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

static bool ask_yesno(const std::string &question, bool default_yes = true) {
  std::string ans;
  std::cout << question << (default_yes ? " [Y/n]: " : " [y/N]: ");
  std::getline(std::cin, ans);
  std::transform(ans.begin(), ans.end(), ans.begin(), ::tolower);
  if (ans.empty()) return default_yes;
  return ans == "y" || ans == "yes";
}

static std::string ask_string(const std::string &question,
                              const std::string &def = "") {
  std::string ans;
  std::cout << question;
  if (!def.empty()) std::cout << " (" << def << ")";
  std::cout << ": ";
  std::getline(std::cin, ans);
  if (ans.empty()) return def;
  return ans;
}

static opg::font_params add_watermark(const std::string &pdf,
                                      const std::string &text,
                                      const std::string &font, int size,
                                      int rotation, const std::string &image) {
  std::cout << "Adding watermark: '" << text << "' font=" << font
            << " size=" << size << " rot=" << rotation << " ... done.\n";
  return opg::font_params::builder()
      .set_text(text)
      .set_font_name(font)
      .set_font_size(size)
      .set_rotation(rotation)
      .build();
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <input_file>\n";
    return 1;
  }

  std::string input_file = argv[1];
  std::filesystem::path input_path(input_file);

  std::string output_pdf = input_path.stem().string() + ".pdf";
  output_pdf = input_path.parent_path().string() + "/" + output_pdf;

  std::cout << "=== OpenPdfGuard ===\n";
  std::cout << "Input: " << input_file << "\n";
  opg::pdf_opt::builder opt = opg::pdf_opt::builder();

  // 2. optional watermark
  if (ask_yesno("Add watermark?", false)) {
    std::string wm_text = ask_string("Watermark text", "CONFIDENTIAL");
    std::string wm_font = ask_string("Font", "Helvetica");
    int wm_size = std::stoi(ask_string("Font size", "24"));
    int wm_rot = std::stoi(ask_string("Rotation degrees", "0"));
    std::string wm_img = ask_string("Image path (leave empty for text)");
    opg::font_params::builder().set_text("test test").build();
    auto watermark =
        add_watermark(output_pdf, wm_text, wm_font, wm_size, wm_rot, wm_img);
    opt.set_watermark(watermark);
  }

  // 3. optional encryption
  if (ask_yesno("Encrypt PDF?", false)) {
    std::string user_pass = ask_string("User password");
    std::string owner_pass = ask_string("Owner password");
    std::cout << "Available permissions:\n";
    for (auto &p : permission_table) std::cout << " - " << p.name << "\n";

    std::cout << "Enter permissions separated by commas (e.g., "
                 "print,copy,fill_and_sign): ";
    std::string line;
    std::getline(std::cin, line);

    opg::pdf_permissions perms = opg::pdf_permissions::none;
    std::stringstream ss(line);
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
      if (!found)
        std::cout << "Warning: unknown permission '" << token << "'\n";
    }

    std::cout << "Final permissions mask: 0x" << std::hex
              << static_cast<uint32_t>(perms) << std::endl;
    opt.set_encryption(user_pass, owner_pass, perms);
  }

  opg::pdf_guard guard;
  guard.convert_file(input_file, output_pdf, opt.build());

  std::cout << "\nAll tasks completed successfully.\nOutput file: "
            << output_pdf << "\n";
  return 0;
}