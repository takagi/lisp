#include <iostream>
#include <string>

#include "lisp/eval.h"
#include "lisp/prin1.h"
#include "lisp/read.h"


void repl() {
    std::string line;
    do {
        std::cout << "> ";
        std::getline(std::cin, line);
        prin1(eval(read(line.c_str())));
        std::cout << std::endl;
    } while (true);
}

int main(int argc, char* argv[]) {
    repl();
    return 0;
}
