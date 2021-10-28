
#include "FileReader.h"
#include "outputWriter/XYZWriter.h"
#include "utils/ArrayUtils.h"

#include <iostream>
#include <list>
#include <outputWriter/VTKWriter.h>

/**** forward declaration of the calculation functions ****/

/**
 * calculate the force for all particles
 */
void calculateF();

/**
 * calculate the position for all particles
 */
void calculateX();

/**
 * calculate the position for all particles
 */
void calculateV();

/**
 * plot the particles to a xyz-file
 */
void plotParticles(int iteration);

constexpr double start_time = 0;
constexpr double end_time = 1000;
constexpr double delta_t = 0.014;

// TODO: what data structure to pick?
std::list<Particle> particles;

int main(int argc, char *argsv[]) {

  std::cout << "Hello from MolSim for PSE!" << std::endl;
  if (argc != 2) {
    std::cout << "Erroneous programme call! " << std::endl;
    std::cout << "./molsym filename" << std::endl;
  }

  FileReader fileReader;
  fileReader.readFile(particles, argsv[1]);

  double current_time = start_time;

  int iteration = 0;

  // for this loop, we assume: current x, current f and current v are known
  while (current_time < end_time) {
    // calculate new x
    calculateX();
    // calculate new f
    calculateF();
    // calculate new v
    calculateV();

    iteration++;
    if (iteration % 10 == 0) {
      plotParticles(iteration);
    }
    std::cout << "Iteration " << iteration << " finished." << std::endl;

    current_time += delta_t;
  }

  std::cout << "output written. Terminating..." << std::endl;



  return 0;
}

void calculateF() {
  std::list<Particle>::iterator iterator;
  iterator = particles.begin();

  for (auto &p1 : particles) {
      std::array<double,3> F_i {0,0,0};
    for (auto &p2 : particles) {
      if (p1.getX() != p2.getX() ){
          double scalar = p1.getM()*p2.getM()/ std::pow(ArrayUtils::L2Norm(p1.getX()-p2.getX()),3);
          std::array<double,3> F_ij = scalar * (p2.getX()-p1.getX());
          F_i = F_i + F_ij;
      }
    }
    p1.updateF(F_i);
  }
}

void calculateX() {
  for (auto &p : particles) {
    std::array<double,3> newX = p.getX() + delta_t*p.getV() + (delta_t*delta_t)/(2*p.getM()) * p.getOldF();
    p.updateX(newX);
  }
}

void calculateV() {
  for (auto &p : particles) {
    std::array<double,3> newV = p.getV() + (delta_t/(2*p.getM())) * (p.getF() + p.getOldF());
    p.updateV(newV);
  }
}

void plotParticles(int iteration) {

    std::string out_name("MD_vtk");
    outputWriter::VTKWriter vtkWriter;
    vtkWriter.initializeOutput(particles.size());
    for(auto &particle : particles){
        vtkWriter.plotParticle(particle);
    }
    vtkWriter.writeFile(out_name,iteration);

}
