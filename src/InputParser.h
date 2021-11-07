//
// Created by qendrim on 07.11.21.
//
#pragma once

const std::string help = "Usage: MolSim -i [filename] -d [delta_t] -e [end_time]";

class InputParser {

private:
    double delta_t = 0;
    double end_t = 0;
    char *fileName = nullptr;

    void check();

public:
    void parseInput(int argc, char *argv[]);

    [[nodiscard]] double getDeltaT() const;

    [[nodiscard]] double getEndT() const;

    [[nodiscard]] char *getFileName() const;

};