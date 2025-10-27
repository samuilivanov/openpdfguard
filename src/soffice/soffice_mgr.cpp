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

#include "soffice_mgr.h"

#include <boost/process/search_path.hpp>
#include <cstdint>
#include <filesystem>
#include <fstream>

namespace {
bool is_soffice_running(uint16_t port = 2083) {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    return false;
  }

  sockaddr_in addr{};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

  bool connected = (connect(sock, (sockaddr*)&addr, sizeof(addr)) == 0);
  close(sock);
  return connected;
}

}  // namespace
namespace opg::soffice {

bool soffice_mgr::start() {
  if (is_running()) {
    return true;
  }

  process_.emplace(
      boost::process::search_path("soffice"), "--headless", "--nologo",
      "--nofirststartwizard", "--pidfile=/tmp/soffice_guard.pid",
      "--accept=socket,host=localhost,port=2083;urp;StarOffice.ServiceManager",
      boost::process::std_out > boost::process::null,
      boost::process::std_err > boost::process::null);

  for (int i = 0; i < 20; ++i) {  // up to ~2s
    if (is_running()) {
      started_by_me_ = true;
      return true;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  return false;
}

void soffice_mgr::shutdown() {
  if (!started_by_me_) {
    return;
  }

  std::ifstream pid_file("/tmp/soffice_guard.pid");
  if (pid_file) {
    pid_t pid = 0;
    pid_file >> pid;
    if (pid > 0) {
      ::kill(pid, SIGTERM);
    }
    std::filesystem::remove("/tmp/soffice_guard.pid");
  }

  process_.reset();
  started_by_me_ = false;
}

bool soffice_mgr::is_running() const { return is_soffice_running(2083); }

}  // namespace opg::soffice
