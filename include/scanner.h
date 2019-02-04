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

#ifndef LOX_CPP_SCANNER_H
#define LOX_CPP_SCANNER_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../include/token.h"

class Scanner {
public:
    explicit Scanner(std::string);
    std::vector<Token> scanToken();

private:
    std::string source_;
    unsigned long start_, current_;
    int line_;
    static const std::map<std::string, TokenType> keywords_;

    bool isEnd();
    bool isDigit(char);
    bool isAlphadigit(char);
    bool match(char);
    char peek();
    char peekNext();
    char advance();
};

#endif //LOX_CPP_SCANNER_H
