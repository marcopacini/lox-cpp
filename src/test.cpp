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

#include "../include/test.hpp"
#include "../include/scanner.hpp"
#include "../include/token.hpp"

#include <map>

TEST_CASE("Test TokenType enum", "[TokenType]")
{
    TokenType tokenType = TokenType::WHILE;
    std::stringstream ss;

    ss << tokenType;
    REQUIRE(ss.str() == "WHILE");
}

TEST_CASE("Test Token class", "[Token]")
{
    TokenType tokenType = TokenType::WHILE;
    std::string lexeme = "while";
    unsigned int line = 1;

    Token token(tokenType, lexeme, line);

    REQUIRE(tokenType == token.type());
    REQUIRE(lexeme == token.lexeme());
    REQUIRE(line == token.line());

    std::stringstream ss;
    ss << token;

    REQUIRE(ss.str() == "WHILE while 1");
}

TEST_CASE("Test Scanner class", "[Scanner]")
{
    SECTION("Scanning empty string") {
        Scanner scanner("");
        auto tokens = scanner.scanToken();

        REQUIRE(tokens.size() == 1);
        REQUIRE(tokens.front().type() == TokenType::END_OF_FILE);
    }

    SECTION("Scanning numbers") {
        std::vector<std::string> dataset {
            "1", "12", "12.3", "12.34"
        };

        std::stringstream buffer;

        for (const auto& number : dataset) {
            buffer << number << " ";
        }

        Scanner scanner(buffer.str());
        auto tokens = scanner.scanToken();

        for (int i = 0; i < static_cast<int>(dataset.size()); i++) {
            REQUIRE(tokens[i].type() == TokenType::NUMBER);
            REQUIRE(tokens[i].lexeme() == dataset[i]);
        }
    }

    SECTION("Scanning strings") {
        std::vector<std::string> dataset {
            "", // empty string
            "Hello, World!",
            "while" // reserved word
        };

        std::stringstream buffer;

        for (const auto& string : dataset) {
            buffer << "\"" << string << "\" ";
        }

        Scanner scanner(buffer.str());
        auto tokens = scanner.scanToken();

        for (int i = 0; i < static_cast<int>(dataset.size()); i++) {
            REQUIRE(tokens[i].type() == TokenType::STRING);
            REQUIRE(tokens[i].lexeme() == dataset[i]);
        }
    }

    SECTION("Scanning reserved words") {
        std::vector<Token> dataset {
            Token(TokenType::AND, "and", 1),
            Token(TokenType::BREAK, "break", 1),
            Token(TokenType::CLASS, "class", 1),
            Token(TokenType::COMMA, ",", 1),
            Token(TokenType::CONTINUE, "continue", 1),
            Token(TokenType::DOT, ".", 1),
            Token(TokenType::ELSE, "else", 1),
            Token(TokenType::EQUAL, "=", 1),
            Token(TokenType::EQUAL_EQUAL, "==", 1),
            Token(TokenType::FALSE, "false", 1),
            Token(TokenType::FOR, "for", 1),
            Token(TokenType::FUN, "fun", 1),
            Token(TokenType::GREATER, ">", 1),
            Token(TokenType::GREATER_EQUAL, ">=", 1),
            Token(TokenType::IF, "if", 1),
            Token(TokenType::LEFT_PAREN, "(", 1),
            Token(TokenType::LEFT_SQUARE, "{", 1),
            Token(TokenType::LESS, "<", 1),
            Token(TokenType::LESS_EQUAL, "<=", 1),
            Token(TokenType::MINUS, "-", 1),
            Token(TokenType::NIL, "nil", 1),
            Token(TokenType::NOT, "!", 1),
            Token(TokenType::NOT_EQUAL, "!=", 1),
            Token(TokenType::OR, "or", 1),
            Token(TokenType::PLUS, "+", 1),
            Token(TokenType::PRINT, "print", 1),
            Token(TokenType::RETURN, "return", 1),
            Token(TokenType::RIGHT_PAREN, ")", 1),
            Token(TokenType::RIGHT_SQUARE, "}", 1),
            Token(TokenType::SEMICOLON, ";", 1),
            Token(TokenType::SLASH, "/", 1),
            Token(TokenType::STAR, "*", 1),
            Token(TokenType::THIS, "this", 1),
            Token(TokenType::TRUE, "true", 1),
            Token(TokenType::VAR, "var", 1),
            Token(TokenType::WHILE, "while", 1),
            Token(TokenType::END_OF_FILE, "", 1)
        };

        std::stringstream buffer;

        for (auto it = dataset.begin(); it != dataset.end(); it++) {
            buffer << it->lexeme() << " ";
        }

        Scanner scanner(buffer.str());
        auto tokens = scanner.scanToken();

        REQUIRE(dataset.size() == tokens.size());

        for (int i = 0; i < static_cast<int>(tokens.size()); i++) {
            CHECK(tokens[i] == dataset[i]);
        }
    }

    SECTION("Unterminated string") {
        Scanner scanner("\"unterminated string...");
        REQUIRE_THROWS(scanner.scanToken());
    }
}