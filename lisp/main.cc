#include <iostream>
#include <string>

#include "eval.h"
#include "prin1.h"
#include "read.h"

void repl() {
    std::string line;
    do {
        std::cout << "> ";
        std::getline(std::cin, line);
        prin1(eval(__read(line.c_str())));
        std::cout << std::endl;
    } while (true);
}

int main(int argc, char* argv[]) {
    repl();
    return 0;
}
