#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Tokenizer/Tokenizer.h"

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

    std::vector<Token> tokens = tokenize(contents);

    std::cout << contents  << std::endl;
    return EXIT_SUCCESS;
}
