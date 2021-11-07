//
// Created by qendrim on 07.11.21.
//

#include <getopt.h>
#include <stdexcept>
#include <iostream>
#include "InputParser.h"


static struct option long_options[] = {
        {"input",   required_argument, nullptr, 'i'},
        {"delta_t", required_argument, nullptr, 'd'},
        {"end_t",   required_argument, nullptr, 'e'},
        {"help",    optional_argument, nullptr, 'h'},
        {nullptr, 0,                   nullptr, 0}
};

void InputParser::parseInput(int argc, char **argv) {
    while (true) {
        int result = getopt_long(argc, argv, "i:d:e:h", long_options, nullptr);
        if (result == -1) {
            break;
        }
        switch (result) {
            case 'i':
                arguments[FILENAME] = optarg;
                break;
            case 'd':
                arguments[DELTA] = optarg;
                break;
            case 'e':
                arguments[END] = optarg;
                break;
            case 'h':
                std::cout << help << std::endl;
                exit(EXIT_SUCCESS);
            case ':':
            case '?':
                std::cerr << "Invalid parameter!\n" << help << std::endl;
                exit(EXIT_FAILURE);
            default:
                break;
        }
    }
}

char* InputParser::getArgument(INPUTKEY key) {
    return arguments[key];
}

InputParser::InputParser() : arguments{}{

}
