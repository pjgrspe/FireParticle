#include <SDL2/SDL.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "Screen.h"
#include "Swarm.h"

using namespace std;
using namespace pjg;

int main(int argc, char *argv[]) {
    //Seed the random number generator using the current time
    srand(time(NULL));

    //Create an instance of the Screen class to manage the display
    Screen screen;
    
    //Initialize the screen; exit if initialization fails
    if(screen.init() == false) {
        cout << "Error initializing SDL." << endl;
    }

    bool running = true; // Flag to control the main loop

    //Create an instance of the Swarm class to manage the particles
    Swarm swarm;

    //Main loop
    while (running) {
        int mouseX, mouseY;
        uint32_t mouseState = SDL_GetMouseState(&mouseX, &mouseY);
        bool isClicking = mouseState & SDL_BUTTON(SDL_BUTTON_LEFT); // Check if left mouse button is pressed

        //Get the elapsed time since SDL started
        int elapsed = SDL_GetTicks();

        //Update the particle system based on the elapsed time
        swarm.update(elapsed);

        //Generate color values that change over time using sine functions
        unsigned char green = (unsigned char)((1 + sin(elapsed * 0.0001)) * 128);
        unsigned char red = (unsigned char)((1 + sin(elapsed * 0.0002)) * 128);
        unsigned char blue = (unsigned char)((1 + sin(elapsed * 0.0003)) * 128);

        //Retrieve the array of particles from the swarm
        const Particle * const pParticles = swarm.getParticles();

        //Loop through each particle in the swarm
        for(int i = 0; i < Swarm::NPARTICLES; i++) {
            Particle particle = pParticles[i];

            //Convert normalized particle coordinates (-1 to 1) to screen coordinates
            int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH / 2;
            int y = particle.m_y * Screen::SCREEN_WIDTH / 2 + Screen::SCREEN_HEIGHT / 2;

            // Make particles brighter when clicking
            if(isClicking) {
                red = min(255, (int)(red * 1.5));
                green = min(255, (int)(green * 1.5));
                blue = min(255, (int)(blue * 1.5));
            }

            //Set the pixel color at the calculated position on the screen
            screen.setPixel(x, y, red, green, blue);
        }

        //Apply blur effect to smooth the particle motion
        screen.boxBlur();

        //Render updated pixels on the screen
        screen.update();

        //Check for user input/events; if the user wants to exit, break the loop
        if(screen.processEvents() == false) {
            break;
        }
    }

    //Cleanup: Close the screen and free resources before exiting
    screen.close();
    
    return 0;
}