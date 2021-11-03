//
// Created by qendrim on 03.11.21.
//

#include <stdexcept>
#include "sstream"
#include "ParticleContainer.h"

ParticleContainer::ParticleContainer(size_t capacity) {
    reserve(capacity);
}

bool ParticleContainer::operator==(ParticleContainer &other) const {
    if (other.size() != this->size()) {
        return false;
    }
    for (size_t i = 0; i < other.size(); i++) {
        if (&operator[](i) != &other.operator[](i)) {
            return false;
        }
    }
    return true;
}

std::string ParticleContainer::toString() const {
    std::stringstream stream;
    stream << "ParticleContainer (size = " << size() << ") {\n";
    for (const auto &p: *this) {
        stream << p.toString() << "\n";
    }
    stream << "}";
    return stream.str();
}

std::vector<ParticlePair> ParticleContainer::pairs() {
    std::vector<ParticlePair> pairs{};
    pairs.reserve(size()*(size()-1)/2); //Small optimization since number of pairs can be calculated in advance
    for (size_t i = 0; i < size(); i++) {
        for (size_t j = i + 1; j < size(); j++) {
            pairs.emplace_back(&operator[](i), &operator[](j));
        }
    }
    return pairs;
}

std::ostream &operator<<(std::ostream &os, const ParticleContainer &pc) {
    return os << pc.toString();
}
