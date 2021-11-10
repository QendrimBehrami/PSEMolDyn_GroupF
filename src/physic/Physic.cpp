//
// Created by qendrim on 10.11.2021
//

#include <iostream>
#include <utility>
#include "Physic.h"
#include "utils/ArrayUtils.h"

Physic::Physic(std::shared_ptr<ParticleContainer> particles, double delta) : forces{}, particles{std::move(particles)},
                                                                                    delta_t{delta} {

}

void Physic::calculate() {
    calculatePositions();
    calculateForces();
    calculateVelocitys();
}

void Physic::calculateForces() {
    //Clear Forces
    for (auto &p: *this->particles) {
        p.setOldF(p.getF());
        p.setF(std::array<double, 3>{0, 0, 0});
    }
    for (auto &force: this->forces) {
        force->calculateForce(this->particles);
    }
}

void Physic::calculatePositions() {
    for (auto &p: *this->particles) {
        std::array<double, 3> newX = p.getX() + delta_t * p.getV() + (delta_t * delta_t) / (2 * p.getM()) * p.getOldF();
        p.setX(newX);
    }
}

void Physic::calculateVelocitys() {
    for (auto &p: *this->particles) {
        std::array<double, 3> newV = p.getV() + (delta_t / (2 * p.getM())) * (p.getF() + p.getOldF());
        p.setV(newV);
    }
}

void Physic::addForceCalculation(const std::shared_ptr<ForceCalculation> &forceCalculation) {
    forces.push_back(forceCalculation);
}
