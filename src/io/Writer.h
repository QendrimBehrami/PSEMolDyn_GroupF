//
// Created by qendrim on 10.11.2021
//

#pragma once

#include <memory>
#include "particles/ParticleContainer.h"

namespace outputWriter {

    class Writer {
    public:
        virtual void initializeOutput(int numParticles) = 0;

        virtual void plotParticles(std::shared_ptr<ParticleContainer> particles, const std::string &filename,
                                   int iteration) = 0;
    };

}

