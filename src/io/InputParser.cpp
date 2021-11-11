//
// Created by qendrim on 07.11.2021
//

#include <getopt.h>
#include <stdexcept>
#include <iostream>
#include "InputParser.h"

static struct option long_options[] = {
        {"filename", required_argument, nullptr, 'f'},
        {"delta_t", required_argument, nullptr, 'd'},
        {"end_t", required_argument, nullptr, 'e'},
        {"help", optional_argument, nullptr, 'h'},
        {"output", optional_argument, nullptr, 'o'},
        {"writer", optional_argument, nullptr, 'w'},
        {"interval", optional_argument, nullptr, 'i'},
        {nullptr, 0, nullptr, 0}
};

void InputParser::parseInput(int argc, char **argv) {
    while (true) {
        int result = getopt_long(argc, argv, "f:d:e:ho:w:i:", long_options, nullptr);
        double temp = 0;
        if (result == -1) {
            break;
        }
        switch (result) {
            case 'f':
                arguments[FILENAME] = optarg;
                break;
            case 'd':
                temp = strtod(optarg, nullptr);
                if (temp <= 0) {
                    error();
                }
                arguments[DELTA] = temp;
                break;
            case 'e':
                temp = strtod(optarg, nullptr);
                if (temp <= 0) {
                    error();
                }
                arguments[END] = temp;
                break;
            case 'o':
                arguments[OUT] = optarg;
                break;
            case 'w':
                if (strcasecmp("XYZ", optarg) == 0) {
                    arguments[WRITER] = outputWriter::XYZ;
                } else if (strcasecmp("VTK", optarg) == 0) {
                    arguments[WRITER] = outputWriter::VTK;
                } else {
                    error();
                }
                break;
            case 'i':
                try {
                    if(*std::get_if<int>(&(arguments[INTERVAL]=std::stoi(optarg)))<=0){ // Ok bissl too much lol
                        error();
                    }
                }
                catch (std::runtime_error &e) { // Catch out of range error for example
                    error();
                }
                break;
            case 'h':
                std::cout << help << std::endl;
                exit(EXIT_SUCCESS);
            case ':':
            case '?':
            default:
                error();
        }
    }
}

InputType InputParser::getArgument(InputKey key) {
    if (arguments.find(key) != arguments.end()) {
        return arguments[key];
    } else {

        return nullptr;
    }
}

InputParser::InputParser() : arguments{} {
    // Provide default values to prevent segfault :(
    arguments[WRITER] = DEFAULT_WRITER;
    arguments[INTERVAL] = DEFAULT_INTERVAL;
    arguments[OUT] = DEFAULT_OUT_NAME;
}

void InputParser::error() {
    std::cerr << "Invalid parameter!\n" << help << std::endl;
    exit(EXIT_FAILURE);
}
