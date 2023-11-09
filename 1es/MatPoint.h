#ifndef _MATPOINT
#define _MATPOINT

#include "Vector3.h"
#include "Particle.h"

class MatPoint: public Particle, public Vector3{
    public:
        //using Particle::Particle; si può omettere
        MatPoint(Particle p, Vector3 a, Vector3 b): Particle(p), Vector3(a), m_vel(b){}
        Vector3 R();
        Vector3 V();
        Vector3 GravField(Vector3);
    private:
        Vector3 m_vel;
};

#endif