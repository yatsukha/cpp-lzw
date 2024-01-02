#pragma once

#include <lzw/types.hpp>
#include <lzw/dict/dict.hpp>

namespace lzw {

  template<std::input_iterator Iter, std::input_iterator Sentinel>
  lzw::encoded_t encode(
    Iter iter,
    Sentinel const& end
  ) {
    lzw::encoded_t encoded;
    lzw::dict dictionary{};

    while (iter != end) {
      auto const [code, next_iter] =
        dictionary.get_and_extend(iter, end);

      encoded.emplace_back(code);
      iter = next_iter;
    }

    return encoded;
  }

}

