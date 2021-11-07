//
// Created by qendrim on 07.11.21.
//
#pragma once

#include <map>
#include <any>

const std::string help = "Usage: MolSim -i [filename] -d [delta_t] -e [end_time]";

enum INPUTKEY{FILENAME,DELTA,END};

class InputParser {

private:
    std::map<INPUTKEY,char*> arguments;

public:
    InputParser();

    void parseInput(int argc, char *argv[]);

    char* getArgument(INPUTKEY key);

};