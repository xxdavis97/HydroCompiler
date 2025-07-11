#pragma once

#include <optional>
#include "Node.hpp"

class Parser {
    public:
        inline explicit Parser(std::vector<Token> tokens) 
            :   m_tokens(std::move(tokens))
        {
        };

        std::optional<Node::Expr> parse_expr() {
            if (peek().has_value() && peek().value().type == TokenType::int_lit) {
                return Node::Expr{.int_lit = consume()};
            } else {
                consume();
                return {};
            }
        }

        std::optional<Node::Exit> parse() {
            std::optional<Node::Exit> exit_node;
            while(peek().has_value()) {
                if (peek().value().type == TokenType::exit) {
                    consume();
                    // auto allows to deduce type from initializer therefore it will implicitly 
                    // convert node expression to boolean which for an optional returns true if optional
                    // has a value.  This is alternative to doing Node::Expr  node_expr = parse_expr() above the
                    // if statement then the if statement being node_expr.has_value()
                    if (auto node_expr = parse_expr()) {
                        
                        exit_node = Node::Exit{ .expr = node_expr.value() };
                    }   else {
                        exit(EXIT_FAILURE);
                    }
                    if (!peek().has_value() || peek().value().type != TokenType::semi) {
                        std::cerr << "Invalid expression" << std::endl;
                        exit(EXIT_FAILURE);
                    }
                    consume();
                } 

            }
            m_index = 0;
            return exit_node;
        }

    private:

        /**
         * @brief peeks at character "ahead" away in source code
         * @param ahead: number of characters to peek ahead
         * @return character at index m_index + ahead
         */
        [[nodiscard]] inline std::optional<Token> peek(int ahead = 0) const {
            if (m_index + ahead >= m_tokens.size()) {
                return {};
            }
            return m_tokens.at(m_index + ahead);
        };

        /**
         * @brief returns the character at our member index and increments the index, this effectively consumes the variable
         * @return value at current index
         */
        inline Token consume() {
            return m_tokens.at(m_index++);
        };
        const std::vector<Token> m_tokens;
        size_t m_index = 0;
};