#include <iostream>
#include <fstream>
#include <optional>
#include <sstream>
#include <vector>

#include "./generation.hpp"

int main(int argc, char *argv[])
{
    // 1. at least 2 command line arguments must be present at all times
    if (argc != 2)
    {
        std::cerr << "Incorrect usage.\nCorrect usage is: oxy <input.oxy>" << std::endl;
        return EXIT_FAILURE;
    }

    // 2. "contents" will contain the whole code written in the input file as it is
    std::string contents;
    {
        std::stringstream contents_stream;
        std::fstream input(argv[1], std::ios::in);
        contents_stream << input.rdbuf();
        contents = contents_stream.str();
    }

    // 3. now we need to lex "contents"
    // 4. for that we'll be needing a list of tokens, which we will define in an enum class

    Tokenizer tokenizer(std::move(contents));
    std::vector<Token> tokens = tokenizer.tokenize(contents);

    Parser parser(std::move(tokens));
    std::optional<NodeProg> prog = parser.parse_prog();

    if (!prog.has_value())
    {
        std::cout << "Invalid Program.\n";
        exit(EXIT_FAILURE);
    }

    Generator generator(prog.value());

    {
        std::fstream file("out.asm", std::ios::out);
        file << generator.gen_prog();
    }

    system("nasm -felf64 out.asm");
    system("ld -o out out.o");

    return EXIT_SUCCESS;
}