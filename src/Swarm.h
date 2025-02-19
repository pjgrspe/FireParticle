#ifndef SWARM_H_
#define SWARM_H_

#include "Particle.h"

namespace pjg {

class Swarm {
public:
    const static int NPARTICLES = 5000;

private:
    Particle *m_pParticles;
    int lastTime;

public:
    Swarm();
    virtual ~Swarm();
    void update(int elapsed);

    const Particle * const getParticles() { return m_pParticles; };
};

} /* namespace pjg */

#endif /* SWARM_H_ */
 