//
// Created by qendrim on 03.11.21.
//

#pragma once

#include <vector>
#include "Particle.h"

class ParticleContainer {

private:

    /**
     * Vector containing all Particles
     */
    std::vector<Particle> particles;

public:

    explicit ParticleContainer(size_t size = 0);

    bool operator==(ParticleContainer &other) const;

    const Particle &operator[](size_t index) const;

    void push_back(const Particle &particle);

    [[nodiscard]] std::vector<std::array<Particle *, 2>> pairs();

    [[nodiscard]] size_t size() const;

    [[nodiscard]] std::string toString() const;


};
