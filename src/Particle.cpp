#include <stdlib.h>
#include <math.h>
#include "Particle.h"

namespace pjg {

//Initializes the particle's position and calls the init function
Particle::Particle(): m_x(0), m_y(0) { 
    init();
}

Particle::~Particle() {
    // TODO Auto-generated destructor stub
}

//Initializes the particle's position, direction, and speed
void Particle::init(){
    //Set x and y position to 0
    m_x = 0;
    m_y = 0;

    //Set direction to a random angle between 0 and 2*PI
    m_direction = (2 * M_PI * rand()) / RAND_MAX;
    //Set speed to a random value between 0 and 0.04
    m_speed = (0.1 * rand()) / RAND_MAX;

    //Square the speed to make the distribution of speeds more realistic
    m_speed *= m_speed;
}

//Updates the particle's position based on its speed and direction
void Particle::update(int interval) {
    //Change direction slightly based on the interval
    m_direction += interval * 0.0003;

    //Calculate the x and y speed components
    double xspeed = m_speed * cos(m_direction);
    double yspeed = m_speed * sin(m_direction);

    //Update the particle's position
    m_x += xspeed * interval;
    m_y += yspeed * interval;

    //Reinitialize the particle if it goes out of bounds
    if(m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1) {
        init();
    }

    //Occasionally reinitialize the particle randomly
    if(rand() < RAND_MAX / 100) {
        init();
    }
}

} /* namespace pjg */
