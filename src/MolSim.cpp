#include "io/FileReader.h"
#include "outputWriter/XYZWriter.h"
#include "utils/ArrayUtils.h"
#include "particles/ParticleContainer.h"
#include "io/InputParser.h"

#include <iostream>
#include <outputWriter/VTKWriter.h>
#include <physic/Gravity.h>

#include "physic/Physic.h"

/**** forward declaration of the calculation functions ****/

/**
 * calculate the force for all particles
 * @param particles Vector containing all particles
 * @param particlePairs Vector containing all particle pairs
 */
void calculateF(ParticleContainer &particles, const std::vector<ParticlePair> &particlePairs);

/**
 * calculate the position for all particles
 * @param particles Vector containing all particles
 */
void calculateX(ParticleContainer &particles);

/**
 * calculate the position for all particles
 * @param particles Vector containing all particles
 */
void calculateV(ParticleContainer &particles);

/**
 * plot the particles to a xyz-file
 * @param particles Vector containing all particles
 * @param iteration
 */
void plotParticles(std::shared_ptr<ParticleContainer> &particles, int iteration);

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

    std::shared_ptr<ParticleContainer> particles(new ParticleContainer());
    FileReader fileReader;
    fileReader.readFile(particles, fileName);

    Physic physic{particles, delta_t};
    Gravity gravity{};
    physic.addForceCalculation(std::make_shared<Gravity>(gravity));

    double current_time = start_time;

    int iteration = 0;

    // for this loop, we assume: current x, current f and current v are known
    while (current_time < end_time) {

        physic.calculate();
        iteration++;
        if (iteration % 10 == 0) {
            plotParticles(particles, iteration);
        }
        std::cout << "Iteration " << iteration << " finished." << std::endl;

        current_time += delta_t;
    }

    std::cout << "output written. Terminating..." << std::endl;

    return 0;
}

void calculateF(ParticleContainer &particles, const std::vector<ParticlePair> &pairs) {

    for (auto &p: particles) {
        p.setOldF(p.getF());
        p.setF(std::array<double, 3>{0, 0, 0});
    }

    for (auto &pair: pairs) {
        Particle &p1 = *pair.first;
        Particle &p2 = *pair.second;
        std::array<double, 3> distance = p1.getX() - p2.getX();
        std::array<double, 3> force =
                (p1.getM() * p2.getM()) / (pow(ArrayUtils::L2Norm(distance), 3)) * (-1 * distance);
        p1.addF(force);
        p2.addF(-1 * force);
    }

}

void calculateX(ParticleContainer &particles) {
    for (auto &p: particles) {
        std::array<double, 3> newX = p.getX() + delta_t * p.getV() + (delta_t * delta_t) / (2 * p.getM()) * p.getOldF();
        p.setX(newX);
    }
}

void calculateV(ParticleContainer &particles) {
    for (auto &p: particles) {
        std::array<double, 3> newV = p.getV() + (delta_t / (2 * p.getM())) * (p.getF() + p.getOldF());
        p.setV(newV);
    }
}

void plotParticles(std::shared_ptr<ParticleContainer> &particles, int iteration) {
    std::string out_name("MD_vtk");
    outputWriter::VTKWriter vtkWriter;
    vtkWriter.initializeOutput(particles->size());
    for (auto &particle: *particles) {
        vtkWriter.plotParticle(particle);
    }
    vtkWriter.writeFile(out_name, iteration);
}