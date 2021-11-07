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

double InputParser::getDeltaT() const {
    return delta_t;
}

double InputParser::getEndT() const {
    return end_t;
}

char *InputParser::getFileName() const {
    return fileName;
}

void InputParser::parseInput(int argc, char **argv) {
    while (true) {
        int result = getopt_long(argc, argv, "i:d:e:h", long_options, nullptr);
        if (result == -1) {
            break;
        }
        switch (result) {
            case 'i':
                fileName = optarg;
                break;
            case 'd':
                delta_t = strtod(optarg, nullptr);
                break;
            case 'e':
                end_t = strtod(optarg, nullptr);
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
    check();
}

void InputParser::check() {
    if (fileName == nullptr) {
        std::cerr << "Failed to resolve fileName!\n" << help << std::endl;
        exit(EXIT_FAILURE);
    } else if (delta_t <= 0) {
        std::cerr << "Invalid delta_t!\n" << help << std::endl;
        exit(EXIT_FAILURE);
    } else if (end_t <= 0) {
        std::cerr << "Invalid end_t!\n" << help << std::endl;
        exit(EXIT_FAILURE);
    }
}
