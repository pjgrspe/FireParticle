
#ifndef PARTICLE_H_
#define PARTICLE_H_

namespace pjg {

// The Particle struct represents a single particle in the simulation
struct Particle {
    double m_x;
    double m_y;
    double m_speed;
    double m_direction;

private:
    //Initializes the particle's position, direction, and speed
    void init();

public:
    //Constructor
    Particle();
    //Destructor
    virtual ~Particle();
    //Updates the particle's position based on its speed and direction
    void update(int interval);
};

} /* namespace pjg */

#endif /* PARTICLE_H_ */
 