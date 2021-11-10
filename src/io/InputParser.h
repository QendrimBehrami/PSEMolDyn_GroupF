//
// Created by qendrim on 07.11.2021
//
#pragma once

#include <map>
#include <variant>
#include <io/OutputWriter.h>

const std::string help = "Usage: MolSim -i [filename] -d [delta_t] -e [end_time]";

enum InputKey {
    FILENAME /// Name of input file as char*
    , DELTA /// Value of delta time as double
    , END /// Value of end time as double
    , OUT /// Output filename as char*
    , WRITER // Output writer type as char*
};

typedef std::variant<char *, double, int> InputType;

class InputParser {

private:
    std::map<InputKey, InputType> arguments;

public:
    InputParser();

    void parseInput(int argc, char *argv[]);

    static void error();

    InputType getArgument(InputKey key);

};