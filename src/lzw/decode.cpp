#include <lzw/decode.hpp>
#include <lzw/alphabet.hpp>
#include <lzw/dict/dict.hpp>

#include <string>

namespace lzw {

  std::string decode(encoded_t const& encoded) {
    std::string accumulated_string;

    std::array<std::string, dict::max_entries> dict;
    size_t next_available_code = 0;

    auto const add_to_dict = [&dict, &next_available_code](std::string&& s) {
      dict[next_available_code++] = std::forward<std::string>(s);
    };

    for (char c = alphabet::min_char; c <= alphabet::max_char; ++c) {
      add_to_dict(std::string(1, c));
    }

    for (size_t i = 0; i < encoded.size(); ++i) {
      auto const code = encoded[i];
      accumulated_string += dict[code];

      if (i + 1 < encoded.size() && next_available_code < dict.size()) {
        auto const next_code = encoded[i + 1];

        // the n+1 problem
        char c = static_cast<size_t>(next_code) == next_available_code
          ? dict[code].front()
          : dict[next_code].front();

        add_to_dict(dict[code] + c);
      }
    }

    return accumulated_string;
  }

}
