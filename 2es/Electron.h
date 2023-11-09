#ifndef _ELECTRON
#define _ELECTRON

#include "Particle.h"

class Electron: public Particle{
 public:
  Electron():Particle(9.1093826e-31,-1.60217653e-19){}
};

#endif
