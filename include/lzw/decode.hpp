#pragma once

#include <lzw/types.hpp>
#include <string>

namespace lzw {

  std::string decode(encoded_t const& encoded);

}
