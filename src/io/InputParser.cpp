//
// Created by qendrim on 07.11.2021
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
        {"output",  optional_argument, nullptr, 'o'},
        {"writer",  optional_argument, nullptr, 'w'},
        {nullptr, 0,                   nullptr, 0}
};

void InputParser::parseInput(int argc, char **argv) {
    arguments[WRITER] = outputWriter::UNDEFINED; // Provide default writer to prevent segfault :(
    while (true) {
        int result = getopt_long(argc, argv, "i:d:e:ho:w:", long_options, nullptr);
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
                if(strcasecmp("XYZ",optarg)==0){
                    arguments[WRITER] = outputWriter::XYZ;
                }
                else if(strcasecmp("VTK",optarg)==0){
                    arguments[WRITER] = outputWriter::VTK;
                }
                else{
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

}

void InputParser::error() {
    std::cerr << "Invalid parameter!\n" << help << std::endl;
    exit(EXIT_FAILURE);
}
