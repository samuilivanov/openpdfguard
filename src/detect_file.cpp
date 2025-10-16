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