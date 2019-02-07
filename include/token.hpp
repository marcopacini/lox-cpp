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

#ifndef LOX_CPP_TOKEN_H
#define LOX_CPP_TOKEN_H

#include <iostream>
#include <string>

enum class TokenType {
    AND,
    BREAK,
    CLASS,
    COMMA,
    CONTINUE,
    DOT,
    ELSE,
    EQUAL,
    EQUAL_EQUAL,
    END_OF_FILE, // EOF is already defined in stdio.h
    FALSE,
    FOR,
    FUN,
    GREATER,
    GREATER_EQUAL,
    IDENTIFIER,
    IF,
    LEFT_PAREN,
    LEFT_SQUARE,
    LESS,
    LESS_EQUAL,
    MINUS,
    NIL,
    NOT,
    NOT_EQUAL,
    NUMBER,
    OR,
    PLUS,
    PRINT,
    RETURN,
    RIGHT_PAREN,
    RIGHT_SQUARE,
    SEMICOLON,
    SLASH,
    STAR,
    STRING,
    THIS,
    TRUE,
    VAR,
    WHILE
};

#define NUM_TOKEN_TYPE 40

std::ostream& operator<<(std::ostream&, TokenType);

class Token {
public:
    explicit Token(TokenType, std::string, unsigned int);
    TokenType type() const;
    std::string lexeme() const;
    unsigned int line() const;
    unsigned int position() const;
    bool operator==(const Token&) const;
    friend std::ostream& operator<<(std::ostream&, const Token&);

private:
    TokenType type_;
    std::string lexeme_;
    unsigned int line_;
};

#endif //LOX_CPP_TOKEN_H
