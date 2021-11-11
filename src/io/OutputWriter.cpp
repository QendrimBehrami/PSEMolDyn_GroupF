//
// Created by qendrim on 10.11.2021
//

#include "OutputWriter.h"

#include <memory>
#include <utility>
#include <iostream>


outputWriter::OutputWriter::OutputWriter(outputWriter::OutputFileType fileType, std::string fileName) : fileType{
        fileType}, fileName{std::move((fileName))} {
    switch (fileType) {
        case XYZ:
            this->writer = std::make_unique<XYZWriter>();
            break;
        case VTK:
            this->writer = std::make_unique<VTKWriter>();
            break;
        default:
            std::cerr << "Failed to recognize fileType!" << std::endl;
    }
}


void outputWriter::OutputWriter::plotParticles(std::shared_ptr<ParticleContainer> particles, int iteration) {
    this->writer->initializeOutput(particles->size());
    this->writer->plotParticles(particles, fileName, iteration);
}
