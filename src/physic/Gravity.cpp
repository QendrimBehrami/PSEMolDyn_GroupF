//
// Created by qendrim on 11/10/21.
//

#include <iostream>
#include <memory>
#include "Gravity.h"
#include "utils/ArrayUtils.h"

void Gravity::calculateForce(std::shared_ptr<ParticleContainer> particles) {

    for (size_t i = 0; i < particles->size(); i++) {
        for (size_t j = i + 1; j < particles->size(); j++) {
            auto *p1 = &particles->operator[](i);
            auto *p2 = &particles->operator[](j);
            std::array<double, 3> distance = p1->getX() - p2->getX();
            std::array<double, 3> force =
                    (p1->getM() * p2->getM()) / (pow(ArrayUtils::L2Norm(distance), 3)) * (-1 * distance);
            p1->addF(force);
            p2->addF(-1 * force);
        }
    }

    /*for (auto &pair: particles->pairs()) {
        Particle &p1 = *pair.first;
        Particle &p2 = *pair.second;
        std::array<double, 3> distance = p1.getX() - p2.getX();
        std::array<double, 3> force =
                (p1.getM() * p2.getM()) / (pow(ArrayUtils::L2Norm(distance), 3)) * (-1 * distance);
        p1.addF(force);
        p2.addF(-1 * force);
    }*/
}
