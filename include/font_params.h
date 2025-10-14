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

#include <string>

namespace opg {

struct font_color {
  float red;
  float green;
  float blue;
};

struct font_params {
  std::string font_name_;
  float font_size_;
  font_color font_color_;
  float rotation;
  float trasperancy;
  std::string text_;

  class builder {
   private:
    std::string font_name_ = "Helvetica";
    float font_size_{64};
    font_color font_color_ = {0.6, 0.6, 0.6};
    float rotation_{0};
    float transparency_{1};
    std::string text_;

   public:
    builder &set_font_name(const std::string &name) {
      font_name_ = name;
      return *this;
    }
    builder &set_font_size(float size) {
      font_size_ = size;
      return *this;
    }
    builder &set_font_color(font_color color) {
      font_color_ = color;
      return *this;
    }

    builder &set_rotation(float rotation) {
      rotation_ = rotation;
      return *this;
      ;
    }

    builder &set_transparency(float transparency) {
      transparency_ = transparency;
      return *this;
    }

    builder &set_text(const std::string &text) {
      text_ = text;
      return *this;
    }

    font_params build() const {
      return font_params{font_name_, font_size_,    font_color_,
                         rotation_,  transparency_, text_};
    }
  };
};
}  // namespace opg