//
// Created by qendrim on 10.11.2021
//
#pragma once


#include <variant>
#include "XYZWriter.h"
#include "VTKWriter.h"
#include "particles/ParticleContainer.h"

namespace outputWriter {
    enum OutputFileType {
        XYZ,
        VTK
    };

    class OutputWriter {
        std::unique_ptr<Writer> writer;
        OutputFileType fileType;
        const std::string fileName;
    public:
        OutputWriter(OutputFileType fileType,std::string fileName);
        void plotParticles(std::shared_ptr<ParticleContainer> particles,int iteration);

    };

}

