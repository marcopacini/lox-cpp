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

#include <algorithm>
#include <utility>
#include <sstream>

#include "../include/scanner.h"

const std::map<std::string, TokenType> Scanner::keywords_ = { // NOLINT(cert-err58-cpp)
        { "and",        TokenType::AND },
        { "break",      TokenType::BREAK },
        { "class",      TokenType::CLASS },
        { "continue",   TokenType::CONTINUE },
        { "else",       TokenType::ELSE },
        { "false",      TokenType::FALSE },
        { "for",        TokenType::FOR },
        { "fun",        TokenType::FUN },
        { "if",         TokenType::IF },
        { "nil",        TokenType::NIL },
        { "or",         TokenType::OR },
        { "print",      TokenType::PRINT },
        { "return",     TokenType::RETURN },
        { "this",      TokenType::THIS },
        { "true",       TokenType::TRUE },
        { "var",        TokenType::VAR },
        { "while",      TokenType::WHILE }
};

bool Scanner::isEnd() {
    return current_ >= source_.length();
}

bool Scanner::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool Scanner::isAlphadigit(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_') || isDigit(c);
}

bool Scanner::match(char c) {
    if (isEnd() || source_[current_] != c) {
        return false;
    }

    current_++;
    return true;
}

char Scanner::peek() {
    if (isEnd()) return '\0';
    return source_[current_];
}

char Scanner::peekNext() {
    if (current_ + 1 >= source_.length()) return '\0';
    return source_[current_+1];
}

char Scanner::advance() {
    current_++;
    return source_[current_ - 1];
}

Scanner::Scanner(std::string source):
    source_(move(source)),
    start_(0),
    current_(0),
    line_(1)
{}

std::vector<Token> Scanner::scanToken() {
    std::vector<Token> tokens;

    while (!isEnd()) {
        start_ = current_;

        char c = advance();
        switch (c) {
            case '\n': {
                line_++;
                break;
            }
            case '(': {
                Token token(TokenType::LEFT_PAREN, "(", line_);
                tokens.push_back(token);
                break;
            }
            case ')': {
                Token token(TokenType::RIGHT_PAREN, ")", line_);
                tokens.push_back(token);
                break;
            }
            case '{': {
                Token token(TokenType::LEFT_SQUARE, "{", line_);
                tokens.push_back(token);
                break;
            }
            case '}': {
                Token token(TokenType::RIGHT_SQUARE, "}", line_);
                tokens.push_back(token);
                break;
            }
            case ',': {
                Token token(TokenType::COMMA, ",", line_);
                tokens.push_back(token);
                break;
            }
            case '.': {
                Token token(TokenType::DOT, ".", line_);
                tokens.push_back(token);
                break;
            }
            case '*': {
                Token token(TokenType::STAR, "*", line_);
                tokens.push_back(token);
                break;
            }
            case '-': {
                Token token(TokenType::MINUS, "-", line_);
                tokens.push_back(token);
                break;
            }
            case '+': {
                Token token(TokenType::PLUS, "+", line_);
                tokens.push_back(token);
                break;
            }
            case ';': {
                Token token(TokenType::SEMICOLON, ";", line_);
                tokens.push_back(token);
                break;
            }
            case '!': {
                if (match('=')) {
                    Token token(TokenType::NOT_EQUAL, "!=", line_);
                    tokens.push_back(token);
                } else {
                    Token token(TokenType::NOT, "!", line_);
                    tokens.push_back(token);
                }
                break;
            }
            case '=': {
                if (match('=')) {
                    Token token(TokenType::EQUAL_EQUAL, "==", line_);
                    tokens.push_back(token);
                } else {
                    Token token(TokenType::EQUAL, "=", line_);
                    tokens.push_back(token);
                }
                break;
            }
            case '<': {
                if (match('=')) {
                    Token token(TokenType::LESS_EQUAL, "<=", line_);
                    tokens.push_back(token);
                } else {
                    Token token(TokenType::LESS, "<", line_);
                    tokens.push_back(token);
                }
                break;
            }
            case '>': {
                if (match('=')) {
                    Token token(TokenType::GREATER_EQUAL, ">=", line_);
                    tokens.push_back(token);
                } else {
                    Token token(TokenType::GREATER, ">", line_);
                    tokens.push_back(token);
                }
                break;
            }
            case '/': {
                if (match('/')) {
                    // one-line comment
                    while (peek() != '\n' && !isEnd()) advance();
                } else if (match('*')) {
                    // multi-line comment
                    while (!(match('*') && match('/')) && !isEnd()) {
                        if (peek() == '\n') line_++;
                        advance();
                    }
                } else {
                    Token token(TokenType::SLASH, "/", line_);
                    tokens.push_back(token);
                }
                break;
            }
            case '"': {
                while (peek() != '"' && !isEnd()) {
                    if (peek() == '\n') line_++;
                    advance();
                }

                if (isEnd()) {
                    throw "unterminated string";
                }

                advance(); // consume the closing " char

                Token token(TokenType::STRING, source_.substr(start_+1,current_-start_-2), line_);
                tokens.push_back(token);
                break;
            }
            default: {
                std::vector<char> ignore{' ', '\t', '\r'}; // skipping chars
                if (std::find(ignore.begin(), ignore.end(), c) != ignore.end()) break;

                if (isDigit(c)) {
                    while (isDigit(peek())) advance();

                    if (peek() == '.' && isDigit(peekNext())) {
                        do {
                            advance();
                        } while (isDigit(peek()));
                    }

                    Token token(TokenType::NUMBER, source_.substr(start_, current_-start_), line_);
                    tokens.push_back(token);
                    break;
                }

                if (isAlphadigit(c)) {
                    while (isAlphadigit(peek())) advance();

                    std::string lexeme = source_.substr(start_,current_-start_);
                    TokenType type = TokenType::IDENTIFIER;

                    auto it = keywords_.find(lexeme);
                    if (it != keywords_.end()) {
                        type = it->second;
                    }

                    Token token(type, lexeme, line_);
                    tokens.push_back(token);
                    break;
                }

                std::stringstream error;
                error << "unknown chars sequence: <" << c << ">";
                throw error;
            }
        }
    }

    Token token(TokenType::END_OF_FILE, "", line_);
    tokens.push_back(token);

    return tokens;
}