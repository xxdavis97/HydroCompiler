#pragma once

#include <string>
#include <stack>

class ParenVerifier {
    public:
        inline explicit ParenVerifier(const std::string &src ) 
            : m_src(std::move(src)) 
        {
        };

        /**
         * @brief Verify that for m_src all open Parens of all types are correctly closed
         * @returns true if the Parens are valid and false if invalid
         */
        inline bool verify() {
            std::stack<char> stack;

            for(char c : m_src) {
                if(c == '(' || c == '[' || c == '{') {
                    stack.push(c);
                }
                if (c == ')') {
                    if (stack.empty() || stack.top() != '(') {
                        return false;
                    }
                    stack.pop();
                }
                if (c == ']') {
                    if (stack.empty() || stack.top() != '[') {
                        return false;
                    }
                    stack.pop();
                }
                if (c == '}') {
                    if (stack.empty() || stack.top() != '{') {
                        return false;
                    }
                    stack.pop();
                }
            }
            return stack.empty();
        }

    private:
        const std::string m_src;

};