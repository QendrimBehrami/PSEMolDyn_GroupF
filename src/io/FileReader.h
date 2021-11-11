/*
 * FileReader.h
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#pragma once

#include "particles/Particle.h"
#include "particles/ParticleContainer.h"

#include <list>
#include <memory>

class FileReader {

public:
  FileReader();
  virtual ~FileReader();

  void readFile(std::shared_ptr<ParticleContainer> &particles, char *filename);
};
