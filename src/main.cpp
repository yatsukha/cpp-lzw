#include <lzw/decode.hpp>
#include <lzw/encode.hpp>

#include <cstdlib>
#include <iostream>
#include <string_view>
#include <vector>

int main(int argc, char const* const* argv) {
  if (argc != 2) {
    std::cerr << "Expected mode argument: '-d' or '-e'." << std::endl;
    std::exit(EXIT_FAILURE);
  }

  bool const decode = std::string_view{argv[1]} == "-d";

  // predefined task code :^)
  if (decode) {
    std::vector<uint16_t> codes;
    uint16_t code;
    // this will end up in a loop if input is not proper
    while (std::scanf("%hu", &code) != EOF) {
      codes.push_back(code);
    }

    std::cout << lzw::decode(codes) << std::endl;
  } else {
    std::string input;
    std::cin >> input;

    auto const encoded = lzw::encode(input.begin(), input.end());

    for (size_t i = 0; i < encoded.size(); ++i) {
      printf("%s%d", i ? " " : "", encoded[i]);
    }
    printf("\n");
  }
}

