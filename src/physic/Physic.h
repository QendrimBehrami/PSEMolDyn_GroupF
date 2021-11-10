//
// Created by qendrim on 10.11.2021
//
#pragma once

#include <memory>
#include "ForceCalculation.h"

class Physic {

private:
    std::vector<std::shared_ptr<ForceCalculation>> forces;
    std::shared_ptr<ParticleContainer> particles;
    double delta_t;

public:
    Physic(std::shared_ptr<ParticleContainer>  particles,double delta);
    void calculate();
    void calculateForces();
    void calculatePositions();
    void calculateVelocitys();
    void addForceCalculation(const std::shared_ptr<ForceCalculation> &forceCalculation);

};
