//
// Created by qendrim on 03.11.2021
//

#include <stdexcept>
#include "sstream"
#include "ParticleContainer.h"

/**
 * @brief Create a new container that encapsulates particles.
 * @param capacity The size of the container that encapsulates the particles.
 */
ParticleContainer::ParticleContainer(size_t capacity) {
    reserve(capacity);
}

/**
 * @brief Define the operator == as comparing whether two containers are equal.
 * @param other The container that needs to be compared.
 * @return The result of the comparison
 */

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

/**
 * @brief Convert the container into string.
 * @return The result of the conversion.
 */
std::string ParticleContainer::toString() const {
    std::stringstream stream;
    stream << "ParticleContainer (size = " << size() << ") {\n";
    for (const auto &p: *this) {
        stream << p.toString() << "\n";
    }
    stream << "}";
    return stream.str();
}
/**
 * @brief Save particles in the form of particle pairs.
 * @return The vector of the particle pair.
 */
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

/**
 * @brief Define the operator << to turn the container into an output stream.
 * @param os The desired output stream.
 * @param pc Containers that need to be output.
 * @return The processed output stream.
 */
std::ostream &operator<<(std::ostream &os, const ParticleContainer &pc) {
    return os << pc.toString();
}
