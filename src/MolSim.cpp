#include "io/FileReader.h"
#include "utils/ArrayUtils.h"
#include "particles/ParticleContainer.h"
#include "io/InputParser.h"

#include <iostream>
#include <memory>
#include <physic/Gravity.h>
#include "physic/Physic.h"
#include "io/OutputWriter.h"

constexpr double start_time = 0;

int main(int argc, char *argsv[]) {
    std::cout << "Hello from MolSim for PSE!" << std::endl;

    //Get all relevant parameters
    InputParser parser{};
    parser.parseInput(argc, argsv);
    auto fileName = std::get<std::string>(parser.getArgument(InputKey::FILENAME));
    double delta_t = std::get<double>(parser.getArgument(InputKey::DELTA));
    double end_time = std::get<double>(parser.getArgument(InputKey::END));
    int interval = std::get<int>(parser.getArgument(InputKey::INTERVAL));
    auto writerFileName = std::get<std::string>(parser.getArgument(InputKey::OUT));
    int fileType = std::get<int>(parser.getArgument(InputKey::WRITER));

    //Setup and fill particle-container
    std::shared_ptr<ParticleContainer> particles(new ParticleContainer());
    FileReader fileReader;
    fileReader.readFile(particles, const_cast<char *>(fileName.c_str()));

    //Setup physics and add Gravity
    Physic physic{particles, delta_t};
    physic.addForceCalculation(std::make_shared<Gravity>());

    //Setup outputWriter
    outputWriter::OutputWriter writer{static_cast<outputWriter::OutputFileType>(fileType), writerFileName};

    //Run iterations
    double current_time = start_time;

    int iteration = 0;

    while (current_time < end_time) {

        physic.calculate();
        iteration++;
        if (iteration % interval == 0) {
            writer.plotParticles(particles, iteration);
        }
        std::cout << "Iteration " << iteration << " finished." << std::endl;

        current_time += delta_t;
    }

    std::cout << "output written. Terminating..." << std::endl;
    return 0;
}