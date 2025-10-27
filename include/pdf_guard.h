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
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>

#include "converter_manager.h"
#include "file_to_pdf.h"
#include "font_params.h"
#include "pdf_file.h"

namespace opg {

void initialize();
void shutdown();

struct pdf_opt {
  bool add_watermark_ = false;
  bool add_encryption_ = false;

  std::string user_password_;
  std::string owner_password_;
  pdf_permissions perms_;
  font_params font_params_;

  // TODO(samuil) reduce the arguments here
  pdf_opt(bool add_watermark, bool add_encryption,
          const std::string& user_password, const std::string& owner_password,
          const pdf_permissions& perms, const font_params& font_params)
      : add_watermark_(add_watermark),
        add_encryption_(add_encryption),
        user_password_(user_password),
        owner_password_(owner_password),
        perms_(perms),
        font_params_(font_params) {}

  class builder {
   private:
    bool add_watermark = false;
    bool add_encryption = false;

    std::string user_password_{};
    std::string owner_password_{};
    pdf_permissions perms_{};
    font_params font_params_{};

   public:
    builder& set_watermark(const font_params& params) {
      add_watermark = true;
      font_params_ = params;
      return *this;
    }
    builder& set_encryption(const std::string& user_password,
                            const std::string& owner_password,
                            const pdf_permissions& permitions) {
      add_encryption = true;
      user_password_ = user_password;
      owner_password_ = owner_password;
      perms_ = permitions;

      return *this;
    }

    pdf_opt build() const {
      return pdf_opt{add_watermark,   add_encryption, user_password_,
                     owner_password_, perms_,         font_params_};
    }
  };
};

class pdf_guard {
 private:
  converter_manager converter_manager_;

 public:
  pdf_guard() = default;
  void add_watermark(std::string_view pdf_filename, const font_params& params);

  void add_encryption(std::string_view pdf_filename,
                      const std::string& userPassword,
                      const std::string& ownerPassword,
                      pdf_permissions protection);

  void convert_to_pdf(std::string_view input, std::string_view output);

  void convert_file(std::string_view input, std::string_view output,
                    const pdf_opt& opt);
};
// detect file type
// list of converters
}  // namespace opg
