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

#include "../include/token.h"

#include <unordered_map>

std::ostream& operator<<(std::ostream& os, const TokenType type)
{
    const static std::unordered_map<TokenType, std::string> map = {
            { TokenType::AND, "AND" },
            { TokenType::BREAK, "BREAK" },
            { TokenType::CLASS, "CLASS" },
            { TokenType::COMMA, "COMMA" },
            { TokenType::CONTINUE, "CONTINUE" },
            { TokenType::DOT, "DOT" },
            { TokenType::ELSE, "ELSE" },
            { TokenType::END_OF_FILE, "EOF" },
            { TokenType::EQUAL, "EQUAL" },
            { TokenType::EQUAL_EQUAL, "EQUAL_EQUAL" },
            { TokenType::FALSE, "FALSE" },
            { TokenType::FOR, "FOR" },
            { TokenType::FUN, "FUN" },
            { TokenType::GREATER, "GREATER" },
            { TokenType::GREATER_EQUAL, "GREATER_EQUAL" },
            { TokenType::IDENTIFIER, "IDENTIFIER" },
            { TokenType::IF, "IF" },
            { TokenType::LEFT_PAREN, "LEFT_PAREN" },
            { TokenType::LEFT_SQUARE, "LEFT_SQUARE" },
            { TokenType::LESS, "LESS" },
            { TokenType::LESS_EQUAL, "LESS_EQUAL" },
            { TokenType::MINUS, "MINUS" },
            { TokenType::NIL, "NIL" },
            { TokenType::NOT, "NOT" },
            { TokenType::NOT_EQUAL, "NOT_EQUAL" },
            { TokenType::NUMBER, "NUMBER" },
            { TokenType::OR, "OR" },
            { TokenType::PLUS, "PLUS" },
            { TokenType::PRINT, "PRINT" },
            { TokenType::RIGHT_PAREN, "RIGHT_PAREN" },
            { TokenType::RIGHT_SQUARE, "RIGHT_SQUARE" },
            { TokenType::SEMICOLON, "SEMICOLON" },
            { TokenType::SLASH, "SLASH" },
            { TokenType::STAR, "STAR" },
            { TokenType::STRING, "STRING" },
            { TokenType::THIS, "THIS" },
            { TokenType::TRUE, "TRUE" },
            { TokenType::VAR, "VAR" },
            { TokenType::WHILE, "WHILE" }
    };

    auto it = map.find(type);
    if (it != map.end()) {
        os << it->second;
    }

    return os;
}

Token::Token(TokenType type, std::string lexeme, int line, int position):
        type_(type),
        lexeme_(std::move(lexeme)),
        line_(line),
        position_(position)
{}

TokenType Token::type() const
{
    return type_;
}

std::string Token::lexeme() const
{
    return lexeme_;
}

int Token::line() const
{
    return line_;
}

int Token::position() const
{
    return position_;
}

std::ostream& operator<<(std::ostream& os, const Token& t) {
    return os << t.type_ << " " << t.lexeme_ << " " << t.line_;
}