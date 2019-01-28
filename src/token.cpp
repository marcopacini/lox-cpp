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

std::ostream& operator<<(std::ostream& os, const TokenType type) {
    switch (type) {
        case TokenType::LEFT_PAREN: {
            os << "LEFT_PAREN";
            break;
        }
        case TokenType::RIGHT_PAREN: {
            os << "RIGHT_PAREN";
            break;
        }
        case TokenType::LEFT_SQUARE: {
            os << "LEFT_SQUARE";
            break;
        }
        case TokenType::RIGHT_SQUARE: {
            os << "RIGHT_SQUARE";
            break;
        }
        case TokenType::COMMA: {
            os << "COMMA";
            break;
        }
        case TokenType::DOT: {
            os << "DOT";
            break;
        }
        case TokenType::MINUS: {
            os << "MINUS";
            break;
        }
        case TokenType::PLUS: {
            os << "PLUS";
            break;
        }
        case TokenType::STAR: {
            os << "STAR";
            break;
        }
        case TokenType::SLASH: {
            os << "SLASH";
            break;
        }
        case TokenType::SEMICOLON: {
            os << "SEMICOLON";
            break;
        }
        case TokenType::NOT: {
            os << "NOT";
            break;
        }
        case TokenType::NOT_EQUAL: {
            os << "NOT_EQUAL";
            break;
        }
        case TokenType::EQUAL: {
            os << "EQUAL";
            break;
        }
        case TokenType::EQUAL_EQUAL: {
            os << "EQUAL_EQUAL";
            break;
        }
        case TokenType::LESS: {
            os << "LESS";
            break;
        }
        case TokenType::LESS_EQUAL: {
            os << "LESS_EQUAL";
            break;
        }
        case TokenType::GREATER: {
            os << "GREATER";
            break;
        }
        case TokenType::GREATER_EQUAL: {
            os << "GREATER_EQUAL";
            break;
        }
        case TokenType::STRING: {
            os << "STRING";
            break;
        }
        case TokenType::NUMBER: {
            os << "NUMBER";
            break;
        }

        case TokenType::IDENTIFIER: {
            os << "IDENTIFIER";
            break;
        }

        case TokenType::TRUE: {
            os << "TRUE";
            break;
        }

        case TokenType::FALSE: {
            os << "FALSE";
            break;
        }

        case TokenType::NIL: {
            os << "NIL";
            break;
        }

        case TokenType::AND: {
            os << "AND";
            break;
        }

        case TokenType::BREAK: {
            os << "BREAK";
            break;
        }

        case TokenType::CLASS: {
            os << "CLASS";
            break;
        }

        case TokenType::CONTINUE: {
            os << "CONTINUE";
            break;
        }

        case TokenType::ELSE: {
            os << "ELSE";
            break;
        }

        case TokenType::FOR: {
            os << "FOR";
            break;
        }

        case TokenType::FUN: {
            os << "FUN";
            break;
        }

        case TokenType::IF: {
            os << "IF";
            break;
        }

        case TokenType::OR: {
            os << "OR";
            break;
        }

        case TokenType::PRINT: {
            os << "PRINT";
            break;
        }

        case TokenType::RETURN: {
            os << "RETURN";
            break;
        }

        case TokenType::THIS: {
            os << "THIS";
            break;
        }

        case TokenType::VAR: {
            os << "VAR";
            break;
        }

        case TokenType::WHILE: {
            os << "WHILE";
            break;
        }

        case TokenType::END_OF_FILE: {
            os << "EOF";
            break;
        }
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