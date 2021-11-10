//
// Created by qendrim on 07.11.2021
//
#pragma once

#include <map>
#include <variant>

const std::string help = "Usage: MolSim -i [filename] -d [delta_t] -e [end_time]";

enum InputKey {
    FILENAME /// Name of input file as char*
    , DELTA /// Value of delta time as double
    , END /// Value of end time as double
};

typedef std::variant<char *, double> InputType;

class InputParser {

private:
    std::map<InputKey, InputType> arguments;

public:
    InputParser();

    void parseInput(int argc, char *argv[]);

    InputType getArgument(InputKey key);

};