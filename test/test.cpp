#include <lzw/decode.hpp>
#include <lzw/dict/dict.hpp>
#include <catch2/catch_all.hpp>

TEST_CASE("Encoder", "Basic") {
  lzw::dict dict;

  REQUIRE(dict.get_and_extend("C").first == 2);
  std::string_view x = "X";
  REQUIRE(dict.get_and_extend(x).second == x.end());

  std::string_view ab = "AB";

  auto const [code, iter] = dict.get_and_extend(ab);
  REQUIRE(code == 0);
  REQUIRE(iter == ab.begin() + 1);
  REQUIRE(dict.get_and_extend(ab).first == 26);
  REQUIRE(dict.get_and_extend(ab).second == ab.begin() + 2);
}

TEST_CASE("Decoder", "Basic") {
  REQUIRE(
    lzw::decode({7, 14, 3, 14, 17, 26, 28, 30, 27, 29, 31, 29}) 
      == "HODORHODORHODORHODOR");
  // the N+1 problem
  // e.g. the only way we can have a n+1 if the next string is
  // is constructed using first character from the previous
  REQUIRE(
    lzw::decode({7, 26}) 
      == "HHH");
}


