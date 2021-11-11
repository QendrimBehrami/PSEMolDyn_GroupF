/*
 * XYZWriter.h
 *
 *  Created on: 01.03.2010
 *      Author: eckhardw
 */

#pragma once

#include "particles/Particle.h"
#include "Writer.h"

#include <fstream>
#include <list>

namespace outputWriter {

class XYZWriter : public Writer{

public:
  XYZWriter();

  virtual ~XYZWriter();

  void plotParticles(std::shared_ptr<ParticleContainer> particles, const std::string &filename,
                     int iteration) override;

    void initializeOutput(int numParticles) override;
};

} // namespace outputWriter
