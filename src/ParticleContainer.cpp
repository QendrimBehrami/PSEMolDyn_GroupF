//
// Created by qendrim on 03.11.21.
//

#include <stdexcept>
#include "sstream"
#include "ParticleContainer.h"

ParticleContainer::ParticleContainer(size_t size) : particles{size} {}

bool ParticleContainer::operator==(ParticleContainer &other) const {
    if (other.size() != this->size()) {
        return false;
    }
    for (size_t i = 0; i < other.size(); i++) {
        if (&particles[i] != &other[i]) {
            return false;
        }
    }
    return true;
}

const Particle &ParticleContainer::operator[](size_t index) const {
    if (index >= size()) {
        throw std::out_of_range("ParticleContainer access out of range!");
    }
    return particles[index];
}

size_t ParticleContainer::size() const { return particles.size(); }

void ParticleContainer::push_back(const Particle &particle) {
    this->particles.push_back(particle);
}

std::string ParticleContainer::toString() const {
    std::stringstream stream;
    stream << "ParticleContainer (size = " << size() << ") {\n";
    for(const auto& p : particles){
        stream << p.toString() << "\n";
    }
    stream << "}";
    return stream.str();
}

std::vector<std::array<Particle*,2>> ParticleContainer::pairs(){
    std::vector<std::array<Particle*,2>> pairs{};
    for(size_t i = 0;i<size();i++){
        for(size_t j = i+1;j<size();j++){
            std::array<Particle*,2> pair = {&particles[i],&particles[j]};
            pairs.push_back(pair);
        }
    }
    return pairs;
}
