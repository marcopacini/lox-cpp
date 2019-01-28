#include <iostream>
#include <string>

#include "../include/token.h"

int main(int argc, char* argv[])
{
    Token token(TokenType::STRING, "Hello, World!", 1, 1);
    std::cout << token << std::endl;

    return 0;
}

