//  MIT License
//
//  Copyright (c) 2019 Marco Pacini
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.

#define CATCH_CONFIG_MAIN

#include "../include/catch.hpp"
#include "../include/token.h"

TEST_CASE("TokenType enum", "[token]")
{
    TokenType tokenType = TokenType::WHILE;
    std::stringstream ss;

    ss << tokenType;
    REQUIRE(ss.str() == "WHILE");
}

TEST_CASE("Token class", "[token]")
{
    TokenType tokenType = TokenType::WHILE;
    std::string lexeme = "while";
    unsigned int line = 1, position = 1;

    Token token(tokenType, lexeme, line, position);

    REQUIRE(tokenType == token.type());
    REQUIRE(lexeme == token.lexeme());
    REQUIRE(line == token.line());
    REQUIRE(position == token.position());

    std::stringstream ss;
    ss << token;

    REQUIRE(ss.str() == "WHILE while 1 1");
}