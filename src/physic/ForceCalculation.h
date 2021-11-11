//
// Created by qendrim on 10.11.2021
//

#pragma once

#include "particles/ParticleContainer.h"

class ForceCalculation{

public:
    virtual void calculateForce(std::shared_ptr<ParticleContainer> particles) = 0;
};