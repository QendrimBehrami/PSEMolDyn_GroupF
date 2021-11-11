//
// Created by qendrim on 07.11.2021
//
#pragma once

#include <map>
#include <variant>
#include <io/OutputWriter.h>

const std::string help = "Usage: MolSim -f [filename] -d [delta_t] -e [end_time]";

constexpr int DEFAULT_WRITER = outputWriter::VTK;
constexpr int DEFAULT_INTERVAL = 10;
const std::string DEFAULT_OUT_NAME = "MD_vtk";

enum InputKey {
    FILENAME /// Name of input file as std::string
    , DELTA /// Value of delta time as double
    , END /// Value of end time as double
    , OUT /// Output filename as std::string
    , WRITER // Output writer type as int
    , INTERVAL // Number of iterations between file writing as int
};

typedef std::variant<std::string, double, int> InputType;

class InputParser {

private:
    std::map<InputKey, InputType> arguments;

public:
    InputParser();

    void parseInput(int argc, char *argv[]);

    static void error();

    InputType getArgument(InputKey key);

};