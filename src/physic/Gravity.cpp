//
// Created by qendrim on 10.11.2021
//

#include <memory>
#include "Gravity.h"
#include "utils/ArrayUtils.h"

void Gravity::calculateForce(std::shared_ptr<ParticleContainer> particles) {
    for (auto &[p1, p2]: particles->pairs()) {
        std::array<double, 3> distance = p1->getX() - p2->getX();
        std::array<double, 3> force =
                (p1->getM() * p2->getM()) / (pow(ArrayUtils::L2Norm(distance), 3)) * (-1 * distance);
        p1->addF(force);
        p2->addF(-1 * force);
    }
}
