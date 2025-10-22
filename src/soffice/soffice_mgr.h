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

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <boost/process.hpp>
#include <optional>

#pragma once

namespace opg::soffice {

class soffice_mgr {
 private:
  std::optional<boost::process::child> process_;
  bool started_by_me_ = false;
  soffice_mgr() = default;

 public:
  static soffice_mgr& instance() {
    static soffice_mgr inst;
    return inst;
  }

  ~soffice_mgr() { shutdown(); }

  bool is_running() const;

  bool start();

  void shutdown();
};
}  // namespace opg::soffice