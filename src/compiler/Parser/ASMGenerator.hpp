#pragma once
 
#include <string> 
#include <sstream>

class ASMGenerator {
     public:
        inline explicit ASMGenerator(Node::Exit root) 
            : m_root(std::move(root))
        {
        };

        [[nodiscard]] std::string generate() const {
            std::stringstream output;
            output << "global _start\n_start:\n";
            output << "    mov rax, 60 \n";
            output << "    mov rdi, " << m_root.expr.int_lit.value.value() << "\n";
            output << "    syscall";
            std::cout << output.str() << std::endl;
            return output.str();
        };

     private:
        const Node::Exit m_root;
};