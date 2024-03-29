#include <unordered_map>
#include <vector>

#pragma once

namespace lydianlang {

std::vector<std::pair<CharacterType, std::vector<char>>> characterRanges = {
    {ct_ampersand, {'&'}},
    {ct_asterisk, {'*'}},
    {ct_atSign, {'@'}},
    {ct_backslash, {'\\'}},
    {ct_bang, {'!'}},
    {ct_caret, {'^'}},
    {ct_colon, {':'}},
    {ct_comma, {','}},
    {ct_dollarSign, {'$'}},
    {ct_doubleQuote, {'\"'}},
    {ct_equals, {'='}},
    {ct_greaterThan, {'>'}},
    {ct_hash, {'#'}},
    {ct_hyphen, {'-'}},
    {ct_identifier,
     {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
      's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
      'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}},
    {ct_leftBracket, {'['}},
    {ct_leftCurly, {'{'}},
    {ct_leftParen, {'('}},
    {ct_lessThan, {'<'}},
    {ct_number, {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}},
    {ct_percent, {'%'}},
    {ct_period, {'.'}},
    {ct_pipe, {'|'}},
    {ct_plusSign, {'+'}},
    {ct_rightBracket, {']'}},
    {ct_rightCurly, {'}'}},
    {ct_rightParen, {')'}},
    {ct_singleQuote, {'\''}},
    {ct_slash, {'/'}},
    {ct_underscore, {'_'}},
    {ct_whitespace, {'\n', '\t', ' '}}};

}