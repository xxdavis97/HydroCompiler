#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Tokenizer/Tokenizer.hpp"
#include "Tokenizer/ParenVerifier.hpp"
#include "Parser/Parser.hpp"
#include "Parser/ASMGenerator.hpp"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Incorrect args" << std::endl;
        std::cerr << "Correct usage: ./hydro <file.hy>" << std::endl;
        return EXIT_FAILURE;
    }
 
    // Reads the file as an fstream variable called input
    std::fstream input(argv[1], std::ios::in);
    if (!input.is_open()) {
        std::cerr << "Could not open the file." << std::endl;
        return EXIT_FAILURE;
    }
    std::stringstream contents_stream;
    contents_stream << input.rdbuf();
    std::string contents = contents_stream.str();
    input.close();

    //todo: why can't we do std::move with contents
    Tokenizer tokenizer(contents);
    std::vector<Token> tokens = tokenizer.tokenize();

    // Don't need tokens anymore so can move to optimize
    Parser parser(std::move(tokens)); 
    std::optional<Node::Exit> tree = parser.parse();

    if (!tree.has_value()) {
        std::cerr << "No exit statements found" << std::endl;
        exit(EXIT_FAILURE);
    }

    ASMGenerator generator(tree.value());
    // Using braces like this scopes the code and it should auto-close the stream
    // didn't do with above stream to highlight both approaches
    {
        std::fstream file("out.asm", std::ios::out);
        file << generator.generate();
    }

    // Can make shell commands directly from c++
    // Generate the assembly code and then assemble it using nasm
    system("nasm -f elf64 out.asm -o out.o");
    // Link using linker
    system("x86_64-elf-ld out.o -o out");

    return EXIT_SUCCESS;
}
