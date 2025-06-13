#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <format>
#include "Token.h"

class Tokenizer {
    public:
        // inline function to optimize for execution performance
        // initializer list  
        inline explicit Tokenizer(std::string &sourceCode ) 
            : m_sourceCode(std::move(sourceCode)) // move takes pointer and passes pointer to the new variable, preventing copies
        {
        };

        /**
         * @brief tokenize the member source code
         * @return vector of tokens given the string source code
         */
        inline std::vector<Token> tokenize( ) {
            std::vector<Token> tokens {};
            std::string buf = "";
            while (peek().has_value()) {
                // ignore whitespace
                if (std::isspace(peek().value())) {
                    consume();
                    continue;
                } else if (std::isalpha(peek().value())) {
                    buf.push_back(consume());
                    // read until the next non-alphanumeric character into the buffer   
                    while (peek().has_value() && std::isalnum(peek().value())) {
                        buf.push_back(consume());
                    }

                    tokenFromBuffer(buf, tokens);
                } else if (std::isdigit(peek().value())) {
                    buf.push_back(consume());
                    // Ensure 0 or 1 decimal
                    int decimalCount = 0;
                    // Determine if double or int 
                    while (peek().has_value() && std::isdigit(peek().value()) || peek().value() == '.') {
                        if (peek().value() == '.') 
                                decimalCount++;       
                            if (decimalCount > 1) 
                                throw std::invalid_argument( "Can't have multiple decimals in a number" );
                            buf.push_back(consume());
                    }
                    tokenFromBuffer(buf, tokens);
                } else if (peek().value() == ';') {
                    buf.push_back(consume());
                    tokenFromBuffer(buf, tokens);
                } else {
                    throw std::invalid_argument( "Could not parse string argument" );
                }
            }
            printTokenVector(tokens);
            return tokens;
        };

    private:
        // warning if don't use the return value with nodiscard
        /**
         * @brief peeks at character "ahead" away in source code
         * @param ahead: number of characters to peek ahead
         * @return character at index m_index + ahead
         */
        [[nodiscard]] inline std::optional<char> peek(int ahead = 0) const {
            if (m_index + ahead >= m_sourceCode.length()) {
                return {};
            }
            return m_sourceCode.at(m_index + ahead);
        };

        /**
         * @brief returns the character at our member index and increments the index, this effectively consumes the variable
         * @return value at current index
         */
        inline char consume() {
            return m_sourceCode.at(m_index++);
        };

        /**
         * @brief given a buffer and a vector of tokens, tokenize buffer, add to vector and clear buffer
         * @param &buf: buffer to tokenize and clear
         * @param &tokens: vector to add token to 
         */
        inline void tokenFromBuffer(std::string &buf, std::vector<Token> &tokens) {
            Token token = bufToToken(buf);
            tokens.push_back(token);
            buf.clear();
        };

        /**
         * @brief given a buffer, return token if found
         * @param buf: buffer to tokenize
         */
        inline Token bufToToken(std::string buf) {
            if (buf == "exit") {
                return {.type = TokenType::exit};
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

        /**
         * @brief Given a vector of tokens, print type and value
         * @param tokens: vector to print
         */
        inline void printTokenVector(std::vector<Token> tokens) {
            for(Token t : tokens) {
                std::cout << std::format("Type: {} Value: {}", static_cast<int>(t.type), t.value.value_or("")) << std::endl;
            }
        };

        const std::string m_sourceCode;
        size_t m_index = 0;
};
