#include <iostream>
#include <string>

#include "./CharacterType.cpp"
#include "./characterRanges.cpp"

#pragma once

namespace sammylang {

// FIXME: This is insanely inefficient. This happens several times for every single input character.
CharacterType charTypeFrom(char character) {
  for (auto typeIndex = 0; typeIndex < characterRanges.size(); typeIndex++) {
    auto entry = characterRanges[typeIndex];
    auto characterType = entry.first;
    auto characterRange = entry.second;
    for (auto charRangeIndex = 0; charRangeIndex < characterRange.size(); charRangeIndex++) {
      char characterInRange = characterRange[charRangeIndex];
      if (character == characterInRange) {
        return characterType;
      }
    }
  }

  std::string warning = "Encountered an invalid token: \"";
  warning += character;
  warning += '"';
  throw std::out_of_range(warning);
}

} // namespace sammylang