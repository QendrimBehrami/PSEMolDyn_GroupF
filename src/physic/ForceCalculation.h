//
// Created by qendrim on 11/10/21.
//

#pragma once

#include "particles/ParticleContainer.h"

class ForceCalculation{

public:
    virtual void calculateForce(std::shared_ptr<ParticleContainer> particles) = 0;
};