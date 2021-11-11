//
// Created by qendrim on 10.11.2021
//

#ifndef PSEMOLDYN_GROUPF_GRAVITY_H
#define PSEMOLDYN_GROUPF_GRAVITY_H


#include "ForceCalculation.h"

class Gravity : public ForceCalculation{

public:
    void calculateForce(std::shared_ptr<ParticleContainer> particles) override;
};


#endif //PSEMOLDYN_GROUPF_GRAVITY_H
