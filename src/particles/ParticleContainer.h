//
// Created by qendrim on 03.11.21.
//
///@brief Encapsulate the molecules
///Use this class to encapsulate molecules.
///It should be possible to iterate over the particles as well as the particle pairs in a simple way.

#pragma once

#include <vector>
#include "Particle.h"

typedef std::pair<Particle*,Particle*> ParticlePair;

class ParticleContainer : private std::vector<Particle>{

public:
    using std::vector<Particle>::emplace_back;
    using std::vector<Particle>::push_back;
    using std::vector<Particle>::size;
    using std::vector<Particle>::operator[];
    using std::vector<Particle>::begin;
    using std::vector<Particle>::end;
    using std::vector<Particle>::reserve;

    explicit ParticleContainer(size_t capacity = 0);

    bool operator==(ParticleContainer &other) const;

    [[nodiscard]] std::vector<ParticlePair> pairs();

    [[nodiscard]] std::string toString() const;

};

std::ostream &operator<<(std::ostream &os,const ParticleContainer &pc);