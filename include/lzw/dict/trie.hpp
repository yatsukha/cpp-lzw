#pragma once

#include <lzw/alphabet.hpp>
#include <lzw/types.hpp>

#include <array>
#include <functional>

namespace lzw {

  struct trie {
    using pointer_type = std::unique_ptr<trie>;
    using ref_wrapper_type = std::reference_wrapper<trie>;

    code_t code;
    std::array<pointer_type, alphabet::size> children{};

    static pointer_type make(code_t const code) {
      return std::make_unique<trie>(code);
    }
  };

  // return a pair of:
  //   - the trie node corresponding to the longest sequence in trie
  //   - iterator past the last character in trie, this is potentially == end 
  template<std::input_iterator Iter, std::input_iterator Sent>
  std::pair<trie::ref_wrapper_type, Iter> find_longest_existing(
    trie::pointer_type const& trie_ptr,
    Iter begin,
    Sent const& end
  ) {
    if (begin == end) {
      return {*trie_ptr, begin};
    }

    auto const& child_ptr = trie_ptr->children[alphabet::to_index(*begin)];

    if (!child_ptr) {
      return {*trie_ptr, begin};
    }

    return find_longest_existing(child_ptr, begin + 1, end);
  }

}
