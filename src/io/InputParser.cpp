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
        double temp = 0;
        if (result == -1) {
            break;
        }
        switch (result) {
            case 'i':
                arguments[FILENAME] = optarg;
                break;
            case 'd':
                temp = strtod(optarg, nullptr);
                if (temp <= 0) {
                    std::cerr << "Invalid parameter!\n" << help << std::endl;
                    exit(EXIT_FAILURE);
                }
                arguments[DELTA] = temp;
                break;
            case 'e':
                temp = strtod(optarg, nullptr);
                if (temp <= 0) {
                    std::cerr << "Invalid parameter!\n" << help << std::endl;
                    exit(EXIT_FAILURE);
                }
                arguments[END] = temp;
                break;
            case 'h':
                std::cout << help << std::endl;
                exit(EXIT_SUCCESS);
            case ':':
            case '?':
            default:
                std::cerr << "Invalid parameter!\n" << help << std::endl;
                exit(EXIT_FAILURE);
        }
    }
}

InputType InputParser::getArgument(InputKey key) {
    if (arguments.find(key) != arguments.end()) {
        return arguments[key];
    } else {
        std::cerr << "Missing parameter!\n" << help << std::endl;
        exit(EXIT_FAILURE);
    }
}

InputParser::InputParser() : arguments{} {

}
