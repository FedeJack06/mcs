#ifndef _ELECTRON
#define _ELECTRON
#include "Particle.h"

class Electron: public Particle{ //9.11e-31 kg 1.6e-19 C 
    public:
        using Particle::Particle;
        Electron(): Particle(9.11e-31, 1.6e-19){}
    private:

};

#endif