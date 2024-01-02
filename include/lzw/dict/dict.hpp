#pragma once

#include <lzw/alphabet.hpp>
#include <lzw/dict/trie.hpp>

#include <string_view>

namespace lzw {

  struct dict {
    size_t constexpr static max_entries = 65'536;

    trie::pointer_type next_trie_node() {
      return trie::make(static_cast<code_t>(next_code++));
    }

    dict() {
      for (auto& trie_node : trie_ptr->children) {
        trie_node = next_trie_node();
      }
    }

    auto get_and_extend(std::string_view const& s) {
      return get_and_extend(s.begin(), s.end());
    }

    template<std::input_iterator Iter, std::input_iterator Sent>
    std::pair<code_t, Iter> get_and_extend(
      Iter begin,
      Sent const& end
    ) {
      auto const [trie_child_node_ptr, first_not_processed] =
        find_longest_existing(trie_ptr, begin, end);

      if (first_not_processed != end 
          && next_code < max_entries) {
        
        trie_child_node_ptr.get().children[
          alphabet::to_index(*first_not_processed)
        ] =
          next_trie_node();
      }

      return {trie_child_node_ptr.get().code, first_not_processed};
    }

   private:
    // the code of the first trie node is never looked at
    trie::pointer_type trie_ptr = trie::make(0);
    size_t next_code = 0;

  };

}
