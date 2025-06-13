#include <string>
#include <vector>
#include <stdexcept>
#include <format>
#include "Token.h"

Token bufToToken(std::string buf) {
    if (buf == "return") {
        return {.type = TokenType::_return};
    }
    if (buf == ";") {
        return {.type = TokenType::semi};
    }
    if (buf.length() > 0 && std::isdigit(buf[0])) {
        if (buf.contains('.')) {
            return {.type = TokenType::doub, .value = buf};
        }
        return {.type = TokenType::int_lit, .value = buf};
    }
    return {};
};

void printTokenVector(std::vector<Token> tokens) {
    for(Token t : tokens) {
        std::cout << std::format("Type: {} Value: {}", static_cast<int>(t.type), t.value.value_or("")) << std::endl;
    }
};

std::vector<Token> tokenize(const std::string &str) {
    std::vector<Token> tokens {};
    for(int i = 0; i < str.length(); i++) {
        std::string buf = "";
        char c = str.at(i);
        // Read into buffer and break on whitespace/endline
        if (std::isalpha(c)) {
            // read c into a buffer variable, this should be done better 
            buf.push_back(c);  
            // read until the next non-alphanumeric character into the buffer   
            while (std::isalnum(str.at(++i))) {
                buf.push_back(str.at(i));
            }
            Token token = bufToToken(buf);
            tokens.push_back(token);
            buf = "";
        } 
        if (std::isdigit(c)) {
            buf.push_back(str.at(i));
            // Ensure 0 or 1 decimal
            int decimalCount = 0;
            // Determine if double or int 
            while (std::isdigit(str.at(++i)) || str.at(i) == '.') {
                if (str.at(i) == '.') 
                    decimalCount++;       
                if (decimalCount > 1) 
                    throw std::invalid_argument( "Can't have multiple decimals in a number" );
                buf.push_back(str.at(i));
            }
            Token token = bufToToken(buf);
            tokens.push_back(token);
            buf = "";
        }
        if (str.at(i) == ';') {
            buf.push_back(str.at(i));
            Token token = bufToToken(buf);
            tokens.push_back(token);
            buf = "";
        }
    }
    printTokenVector(tokens);
    return tokens;
};