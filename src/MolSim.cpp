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
double end_time;
double delta_t;

int main(int argc, char *argsv[]) {
    std::cout << "Hello from MolSim for PSE!" << std::endl;

    InputParser parser{};
    parser.parseInput(argc, argsv);
    auto fileName = std::get<char *>(parser.getArgument(InputKey::FILENAME));
    delta_t = std::get<double>(parser.getArgument(InputKey::DELTA));
    end_time = std::get<double>(parser.getArgument(InputKey::END));

    char *outFile = std::get<char *>(parser.getArgument(InputKey::OUT));
    std::string writerFileName = outFile == nullptr ? "MD_vtk" : outFile;

    int fileType = std::get<int>(parser.getArgument(InputKey::WRITER));
    if (fileType == outputWriter::UNDEFINED) {
        fileType = outputWriter::VTK;
    }

    std::shared_ptr<ParticleContainer> particles(new ParticleContainer());
    FileReader fileReader;
    fileReader.readFile(particles, fileName);

    Physic physic{particles, delta_t};
    physic.addForceCalculation(std::make_shared<Gravity>());

    outputWriter::OutputWriter writer{static_cast<outputWriter::OutputFileType>(fileType), writerFileName};

    double current_time = start_time;

    int iteration = 0;

    // for this loop, we assume: current x, current f and current v are known
    while (current_time < end_time) {

        physic.calculate();
        iteration++;
        if (iteration % 10 == 0) {
            writer.plotParticles(particles, iteration);
        }
        std::cout << "Iteration " << iteration << " finished." << std::endl;

        current_time += delta_t;
    }

    std::cout << "output written. Terminating..." << std::endl;

    return 0;
}