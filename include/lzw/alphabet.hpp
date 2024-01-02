#pragma once

#include <cassert>
#include <cstddef>

namespace lzw::alphabet {

  inline auto constexpr min_char = 'A';
  inline auto constexpr max_char = 'Z';

  inline size_t constexpr size = max_char - min_char + 1;

  inline size_t to_index(char const c) {
    assert(c >= min_char);
    assert(c <= max_char);

    return c - 'A';
  }

}
